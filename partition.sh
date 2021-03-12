#!/bin/bash

function unmount() {
    echo "Unmounting"
    umount /dev/sda?
    # Remove the mnt sda(1/2)
    echo "Removing /mnt/sda"
    rm -rf /mnt/sda?
}

function sleeping() {
    for i in 5 4 3 2 1
    do
        # if variable i is equal to 1 then dont add dots.
        if [ "$i" -eq 1 ]
        then
            # print a new line
            printf "%d\n" "$i"
        else
            # Print on the same line
            printf "%d ... " "$i"
        fi
        sleep 1
    done
}

# Delete the disk partition
printf "Deleting the old partition"
if (echo d; echo w) | fdisk /dev/sda;
then
    printf "Success!\n"
else
    printf "Failed!\nExiting\n"
    # Exiting
    set -e
fi

# clears partition table
printf "Cleaning partition table ... "
if dd if=/dev/zero of=/dev/sda bs=4096 count=10;
then
    printf "Success!\n"
else
    printf "Failed!\nExiting\n"
    # Exits
    set -e
fi

# create the first partition
printf "Creating first partition ... "

if (echo n; echo p; echo 1; echo; echo +27000M; echo w) | fdisk /dev/sda;
then
    printf "Success!\n"
else
    printf "Failed!\nRead error message from fdisk\nExiting!\n"
    set -e
fi

unmount

# create the second partition
printf "Creating second partition\n"
if (echo n; echo p; echo 2; echo; echo; echo w) | fdisk /dev/sda;
then
    printf "Successfully created the second partition!\n"
else
    printf "Failed to created the second partition!\nRead error message from fdisk\nExiting!\n"
    set -e
fi

# Unmount
unmount

# specify first partition is FAT32
printf "Specify first partition is FAT32\n"
if (echo t; echo b; echo c; echo w) | fdisk /dev/sda;
then
    printf "Successfully specified first partition as FAT32!\n"
else
    printf "Failed to specify first partition as FAT32!\nRead error message from fdisk\nExiting!\n"
    set -e
fi

printf "Format the first partition to FAT32 ... "
if mkfs.fat /dev/sda1;
then
    printf "Successful!\n"
else
    printf "Failed!\nCannot make /dev/sda1 to FAT32\n"
    # Exit, dont continue
    set -e
fi

printf "Format the second partition to Linux EXT4 ... "
if mkfs.ext4 /dev/sda2;
then
    printf "Success!\n"
else
    printf "Failed!\nCannot make /dev/sda2 to Linux EXT4\n"
    # Exit, dont continue
    set -e
fi

echo "Unmounting"
unmount

printf "Waiting 5 seconds ... "
# Wait 5 seconds
sleeping

echo "Unmounting again ... "
# Unmount again for some reason
unmount

# Creating 'arduino' folder structure...
printf "Creating 'arduino' folder structure ..."
if mkdir -p /mnt/sda1;
then
    printf "Successfully created /mtn/sda1\n"
else
    printf "Failed!\nCannot create /mnt/sda1 ... "
    if [ -d "/mnt/sda1"]
    then
        printf "folder exists, no worries! Continue\n"
    else
        printf "folder do not exists.\nExiting!\n"
        set -e
    fi
fi

printf "Mounting /dev/sda1 onto /mnt/sda1 ... "
if mount /dev/sda1 /mnt/sda1;
then
    printf "Success!\n"
else
    printf "Failed!\nExiting!\n"
    # exit
    set -e
fi

printf "Creating /mnt/sda1/arduino/www ... "
if mkdir -p /mnt/sda1/arduino/www;
then
    printf "Success!\n"
else
    # Failed but we can still see if the folder exists
    printf "Failed ... "
    if [ -d /mnt/sda1/arduino/www ]
    then
        printf "Folder exists, no worries.\nContinue\n"
    else
        printf "Folder exists\nExiting\n"
        # Exiting
        set -e
    fi
fi

# Unmount again
echo "Unmounting"
unmount

# Copy files from
printf "Copying files from Arduino Yun flash to micro SD card ..."
if mkdir -p /mnt/sda2;
then
    printf "Success!\n"
else
    printf "Failed ... "
    if [ -d /mnt/sda2 ]
    then
        printf "folder exists, no worries\nContinue!\n"
    else
        printf "Folder do not exists!\nExiting\n"
        set -e
    fi
fi

printf "Mounting /dev/sda2 onto /mnt/sda2 ... "
if mount /dev/sda2 /mnt/sda2;
then
    printf "Success!\n"
else
    printf "Failed!\nExiting\n"
    # exit
    set -e
fi

printf "Running rsync .. "
# rsync is a file transfer program capable of efficient remote update via a fast differencing algorithm.
if (rsync -a --exclude=/mnt/ --exclude=/www/sd /overlay/ /mnt/sda2/);
then
    printf "Success!\n"
else
    printf "Failed!\nExiting\n"
    set -e
fi

echo "Unmounting"
unmount

printf "Creating swap ... "
uci add fstab swap
uci set fstab.@swap[0].target=/swap
uci set fstab.@swap[0].device=/overlay/swapfile
uci set fstab.@swap[0].enabled=1
uci set fstab.@swap[0].enabled_fsck=0
uci commit
printf "Done\n"

printf "Enabling micro SD as additional disk space ... "
uci add fstab mount
uci set fstab.@mount[0].target=/overlay
uci set fstab.@mount[0].device=/dev/sda2
uci set fstab.@mount[0].fstype=ext4
uci set fstab.@mount[0].enabled=1
uci set fstab.@mount[0].enabled_fsck=1
uci set fstab.@mount[0].options=rw,sync,noatime,nodiratime
uci commit

printf "DONE. We are now DONE!"

# Example took from school example and made it work with latest
# 
import os, uuid, sys, time, re
from azure.storage.blob import BlobServiceClient
from azure.core.exceptions import HttpResponseError, ResourceExistsError, ResourceNotFoundError

# replace yourAccount with your own account.
CONNECTION = "yourAccount"
# Grab this from "Storage account" -> Your account -> "Access keys" -> Key 1 (Not the connection string)
CREDENTIALS = "replaceMe"

class blober(object):
    def __init__(self, name, connection, credential):
        # Useful for the class to operate.
        self.containerName = name
        self.con = connection + ".blob.core.windows.net"
        self.cred = credential
        # clients
        self.clientBlock = None
        self.clientContainer = None
        self.clientBlob = None
        # Paths
        self.localPath = None
        self.localFile = None
        self.localFilePath = None
        self.remotePath = None
        self.remoteFilePath = None

    def start(self):
        # Start by trying to use the functions below
        try:
            self.createClientContainer()
            self.fileHandler()
            self.listBlobs()
            self.downloadBlob()
        # Catch KeyBoardInterrupt (ctrl + c)
        except KeyboardInterrupt:
            print("\nClass 'Blober' has been interrupted. Stopping")
        # Catch ValueError as ve (use default text in ve string)
        except ValueError as ve:
            print(ve)
            return
        # Catch ResourceNotFoundError as rnfe (use default text in rnfe string)
        except ResourceNotFoundError as rnfe:
            print(rnfe)
        # Catch ResourceExistsError as rnfe (use default text in ree string)
        except ResourceExistsError as ree:
            if ree == 'The specified container is being deleted. Try operation later.':
                print("It might take up to 60 seconds before being totally removed "
                      "from the azure storage.. restarting in 60 seconds.");
            elif ree == 'The specified container does not exist.':
                pass
            else:
                if self.containerName is not None:
                    print("\nResource aleady exists!")
                    self.clientBlock.delete_container(
                        self.containerName
                    )
            # Now we wait.
            self.wait();
            # Recursion
            self.start()
        # Catch ContainerNotFound as cnf (use default text in cnf string)
        except ContainerNotFound as cnf:
            print(cnf)
        # Catch FileNotFoundError as fnfe (use default text in fnfe string)
        except FileNotFoundError as fnfe:
            print(fnfe)
        except Exception as e:
            # print("Caught: {0}" . format(e))
            # TypeError / /tmp/example.py / 2
            print(type(e) . __name__, __file__, e . __traceback__ . tb_lineno)
        # End by stopping it all.
        finally:
            self.stop()

    # Create blob from contianer
    def createClientContainer(self):
        # Send con and cred to BlobServiceClient
        self.clientBlock = BlobServiceClient(
            self.con, self.cred
        )
        # Send containerName to create_container
        self.clientContainer = self.clientBlock.create_container(
            self.containerName
        )

    # File handler. Take care of the files.
    def fileHandler(self):
        # Create a file in Documents to test the upload and download.
        self.localPath = os.path.abspath(
            os.path.curdir
        )
        # Ask the user about input
        self.localFile = input("Enter file name to upload : ")
        self.localFilePath = os.path.join(
            self.localPath, self.localFile
        )
        # Write text to the file, these just live within this function
        file = open(self.localFilePath,  'w')
        fileText = input("Enter text to file {0}: " . format(self.localFile))
        file.write(fileText)
        file.close()
        # BlobClient = clientBlob
        self.clientBlob = self.clientBlock.get_blob_client(
            container = self.containerName, blob = self.localFile
        )
        # Upload the created file
        with open(self.localFilePath, "rb") as data:
            self.clientBlob.upload_blob(data)

    def listBlobs(self):
        # List the blobs in the container
        print("\nListing all the blobs in the container")
        generator = self.clientContainer.list_blobs()
        # List all the blobs
        for blob in generator:
            print("\tBlob name: " + blob.name)

    def downloadBlob(self):
        # Join the path
        self.remoteFilePath = os.path.join(
            self.localPath,
            str.replace(self.localFile, '.txt', '_DOWNLOADED.txt')
        )
        print("\nDownloading blob to " + self.remoteFilePath)
        # downloadedFile just live withing this function
        with open(self.remoteFilePath, "wb") as downloadFile:
            downloadFile.write(
                self.clientBlob.download_blob().readall()
            )

    def stop(self):
        sys.stdout.write("Sample finished running. When you hit <any key>, "
                         "the sample will be deleted and the sample "
                         "application will exit.")
        sys.stdout.flush()
        input()

        # Clean up resources.
        # Delete the container at Azure if we got that far..
        if self.containerName is None or self.clientBlock is None:
            # pass. Do nothing
            pass
        else:
            # Else delete container
            self.clientBlock.delete_container(self.containerName)

        # if file is not set (skipping steps)
        if self.localFilePath is None or self.remoteFilePath is None:
            pass
        else:
            # Otherwise check if path exists.
            if not os.path.exists(self.localFilePath):
                # Raise an error with custom text
                raise FileNotFoundError(
                    "Cant find the file {0}" . format(self.localFilePath)
                )
            # Otherwise check if path exists.
            elif not os.path.exists(self.remoteFilePath):
                # Raise an error with custom text
                raise FileNotFoundError(
                    "Cant find the file {0}" . format(self.remoteFilePath)
                )
            else:
                # Remove the files, the one we downloaded (remote) and our local
                os.remove(self.localFilePath)
                os.remove(self.remoteFilePath)

    def wait(self):
        # Set timer to 0
        sleeps = 0
        sleepInterval = 10/4
        waitTime = 60
        startTime = time.time()
        self.waiting("Waiting", sleepInterval)
        sleeps += sleepInterval
        self.waiting(".", sleepInterval)
        sleeps += sleepInterval
        self.waiting(".", sleepInterval)
        sleeps += sleepInterval
        self.waiting(".", sleepInterval)
        sleeps += sleepInterval
        # choice = input("Enter Q to quit")
        while True:
            # if time is greater than start time + 60 seconds.
            if time.time() > (startTime + waitTime):
                # Tell the user that we're should be on the safe side
                print("\nThe blob should be deleted by now. Restarting!")
                # Stop the loop here.
                break;
            # Print every 10 second (just so we dont fall asleep)
            # This will peint without a newline (\n)
            #print("...{0}" . format(sleeps), end="")
            self.waiting(sleeps, sleepInterval)
            sleeps += sleepInterval
            self.waiting(".", sleepInterval)
            sleeps += sleepInterval
            self.waiting(".", sleepInterval)
            sleeps += sleepInterval
            self.waiting(".", sleepInterval)
            sleeps += sleepInterval
        print()

    def waiting(self, text, interval):
        sys.stdout.write(str(text))
        sys.stdout.flush()
        time.sleep(interval)


# Main method.
if __name__ == '__main__':
    blobName = input("Enter the name of your blob: ")
    bl = blober(blobName, CONNECTION, CREDENTIALS)
    bl.start()


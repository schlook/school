/*
 * Program by Niklas Karlsson
 * Copyright (c) Nikas 'schlook' Karlsson
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <strings.h>

// Globals
_Bool sex;                                                                      // Since gender is taken we have to use the other word for gender.. sex.
long long int ss;                                                               // Social Security Digit.
char gender[100];                                                               // Needed for compare

/*
 * Headers
 */
static _Bool checkGender(void);
static int socialSecurityControl(void);
static int getGender(void);
static int countDigits(long long int no);

/*
 * Main function
 */
int main(void)
{
    printf("Hello and welcome to the social security number checker.\nLet's begin!\n");
    getGender();                                                                // Calling mr gender calling mr wrong
    socialSecurityControl();                                                    // Calling social security control

    return 0;
}

/*
 * Try to get the user to input his/hers gender
 */
static int getGender(void)
{
    printf("Are you a boy or a girl? ");                                        // The million dollar question.
    scanf("%s", &gender);                                                       // User input.

    // Look for some words describing "men", both swedish and english
    if ((!stricmp(gender, "male")) || (!stricmp(gender, "man")) ||
        (!stricmp(gender, "boy")) || (!stricmp(gender, "kille")) ||
        (!stricmp(gender, "m")) || (!stricmp(gender, "b")) ||
        (!stricmp(gender, "k")))
    {
        sex = 0;                                                                // Hooray! It's a man!
        // strcpy(gender, "boy");                                                  // For debug purpose.
    }
    // Look for some words describing "women", both swedish and english
    else if ((!stricmp(gender, "female")) || (!stricmp(gender, "woman")) ||
             (!stricmp(gender, "kvinna")) || (!stricmp(gender, "f")) ||
             (!stricmp(gender, "girl")) || (!stricmp(gender, "tjej")) ||
             (!stricmp(gender, "t")) || (!stricmp(gender, "g")) ||
             (!stricmp(gender, "w")))
    {
        sex = 1;                                                                // Hooray! It's a woman!
        // strcpy(gender, "girl");                                                 // For debug purpose.
    }
    // Yeah I know the term is socially accepted but not accepted as social security. Sorry!
    else if (!stricmp(gender, "hen"))
    {
        printf("Sorry! I can't translate \"hen\" with a social security number.\nPsst! I'm very discrete, not gonna reveal your gender to anyone. *pinky promise*\n\a");
        fflush(stdin);                                                          // Flush after you wipe.
        fflush(stdout);                                                         // Flush after you wipe.
        getGender();                                                            // Go back and try again. (This could continue for an eternity of the user doesn't understand)
    }
    // This is the other stuff, that we dont care or dont wanna look for.
    else
    {
        // Just... break.
        printf("Error.. Error.. you.. broke.. me..\n(Terminating) AAIIII!!! I had so much to live fo..\n\a");
        exit(0);
    }

    return 0;
}

/*
 * Just check if the input man/woman is considered the same when doing math
 */
static int socialSecurityControl(void)
{
    printf("Enter your social security number.\nFormat is YYMMDDNNNN or YYYYMMDDNNNN: ");
    scanf("%lld", &ss);                                                         // Somehow if we dont force a leading zero ppl born in the 20th century is not accepted. Strange but works now

    int c = countDigits(ss);                                                    // so we dont have to call the function over and over.. save some speed here. :)

    if ((c < 10) || (c > 12))
    {
        if (c == 9)
        {
            // if born between 2000 and 2010 then we don't get the leading zero.
            // if i add the %010lld it counts all inputs as atleast 10 digits.
            // So just continue, nothing see here folks!
            // It could also be wrong, but i'm willing to take that for now.
        }
        else
        {
            printf("Sorry the social security number must be between 10 and 12 digits, you entered %d digits.\n\a", c);
            fflush(stdin);                                                      // Flush after you wipe.
            fflush(stdout);                                                     // Flush after you wipe.
            socialSecurityControl();                                            // Go back up and start over.
        }
    }

    _Bool someGender = checkGender();

    /*
     * Do a check for the social security number and if we also set the gender before.
     * odd gender and odd sex = male (1, 3, 5, 7, 9)
     * even gender and even sex = female (0, 2, 4, 6, 8)
     * We only have _Bool in our system, so we just check for 1 or 0.
     *
     * Here is how it should work:
     * if gender = 1 and sex = 1   (sum will be 1)
     * if gender = 0 and sex = 0   (sum will be 1)
     *
     * if gender = 1 and sex = 0   (sum will be 0)
     * if gender = 0 and sex = 1   (sum will be 0)
     *
     * if the sums are 1 (either one)  then it's correct
     * if the sums are 0 (both)        then it's incorrect
     */
    if ((someGender && sex) || (!someGender && !sex))
    {
        printf("The social security number is correct!\n");                     // It sure was OK
        exit(0);
    }
    else
    {
        printf("The social security number is incorrect!\n\a");                 // No it's not OK, alert the user
        fflush(stdin);                                                          // Flush after you wipe.
        fflush(stdout);                                                         // Flush after you wipe.
        socialSecurityControl();
    }

    return 0;
}

/*
 * Returning 1/0, set this to _Bool just to not see any other results.
 */
static _Bool checkGender(void)
{
    ss /= 10;                                                                   // Divide with ten, so we get rid of the last number Since it's not a double or float
    return ((ss % 2) == 0);                                                     // Is it divisable with 2? odd = female, even = male
}

/*
 * Same principle as the above function, with an increment for each digits counted.
 */
static int countDigits(long long int no)
{
    int nl = 0;                                                                 // Always start at zero.
    while (no != 0)                                                             // Loop as long as 'no' is not euqal to 0
    {
        no /= 10;                                                               // Get rid of the last digit with each loop until we reach 0 (not divisable any more)
        nl++;                                                                   // Increment by one
    }

    return nl;
}

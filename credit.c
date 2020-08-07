#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdbool.h>
#include <math.h>

//on error returns [400-499];

int Luhns(long cn); //declaring Luhns(long) function: checks that number is valid based on summation algorithm, cn is card number input by user
int CardType(long cn);//declaring CardType (long) function, checks card type amex, mc or visa


/* User interface & main function */
int main(void)
{
    /* get input */
    long cn = get_long("Number: \n"); //request cn from user
    long cn_copy = cn; //store cn in backup

    /* check */
    CardType(cn);
    //printf("CardType Passed. Output %i\n",CardType(cn));
    Luhns(cn);
    //printf("Luhns passed. Output %i \n", Luhns(cn));

    /* output*/
    if (Luhns(cn)==400 ||CardType(cn)==400)
    {
        printf("Error found. Check input.\n");
        return 400;
    }
    else if (Luhns(cn) == 1)
    {
        printf("INVALID\n");
        return 0;
    }
    else if (Luhns(cn) == 0)
    {
        if (CardType(cn) == 1)
        {
            printf("AMEX\n");
        }
        else if (CardType(cn)==2)
        {
            printf("VISA\n");
        }
        else if (CardType(cn)==3)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}


/* function definitions*/

int CardType(long cn) // returns 1 if amex, 2 if visa, 3 if mc, 4 if invalid
{
    int n = floor(log10(labs(cn))) + 1; // gets length of cn;
    int ct = 400;

    if (n == 15 && ((cn >= 340000000000000 && cn < 350000000000000) || (cn >= 370000000000000 && cn < 380000000000000))) //check amex
    {
        ct = 1;
    }
    else if (n==13 && cn >= 4000000000000 && cn < 5000000000000) //check 13 digit visa
    {
        ct = 2;
    }
    else if (n==16) //check 16 digit cards (visa or mc)
    {
        if (cn >= 4000000000000000 && cn < 5000000000000000) //check visa
        {
            ct = 2;
        }
        else if (cn >= 5100000000000000 && cn <5600000000000000) //check mc
        {
            ct = 3;
        }
    }
    else if (cn)
    {
        return 4;
    }
    return ct;
}


int Luhns (long cn) //returns 0 if valid, 1 if invalid, 400+ if error
{
    int ln = floor(log10(labs(cn))) + 1; // gets length of cn
    int m =ln/2;//divide length by two
    int n = m+ln%2; //add 1 of length is odd, 0 if it's even
    int odddigits[n];
    int evendigits[m]; //array for holding elements of sumation
    int i = 0;

    do //fill arrays of odd and even digits (counting from the back)
    {
        odddigits[i] = (int)(cn%10); //store last digit in odds array
        cn /= 10; //drop last digit
        evendigits[i] = (int)(cn%10)*2; //store last digit, doubled, in evens array
        cn/= 10;//drop doubled digit
        i ++;
    }
    while (cn>1);

    int oddsum =0;
    int evensum =0;

    for (i=0;i<n; i++) //sum odd digits
    {
        //printf("Current odddigits item = %i\n",odddigits[i]);
        if (odddigits[i] >=0)
        {
            oddsum += odddigits[i];
        }
        else
        {
            printf("Error. Negative digit passed to algorithm expecting 0 or greater.\n");
            return 400;
        }
    }

    for (i=0;i<m;i++) //sum even digits
    {
        if (evendigits[i]<=9 && evendigits[i]>=0)
        {
            evensum += evendigits[i];
        }
        else if (evendigits[i]>9)
        {
            evensum += evendigits[i]%10;
            evensum += (evendigits[i]/10)%10;
        }
        else
        {
            printf("Error. Negative digit passed to algorithm expecting 0 or greater.\n");
            return 400;
        }
    }
    int totalsum = evensum + oddsum;
    if (totalsum%10 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
#include <cs50.h>
#include <stdio.h>

long calculate_length(long num);

int main(void)
{
    long cc;

    // Get credit card number for user
    cc = get_long("Number: ");

    // Store all the place values
    long first = cc % 10;
    long second = (cc % 100) / 10;
    long third = (cc % 1000) / 100;
    long fourth = (cc % 10000) / 1000;
    long fifth = (cc % 100000) / 10000;
    long sixth = (cc % 1000000) / 100000;
    long seventh = (cc % 10000000) / 1000000;
    long eighth = (cc % 100000000) / 10000000;
    long ninth = (cc % 1000000000) / 100000000;
    long tenth = (cc % 10000000000) / 1000000000;
    long eleventh = (cc % 100000000000) / 10000000000;
    long twelfth = (cc % 1000000000000) / 100000000000;
    long thirteenth = (cc % 10000000000000) / 1000000000000;
    long fourteenth = (cc % 100000000000000) / 10000000000000;
    long fifteenth = (cc % 1000000000000000) / 100000000000000;
    long sixteenth = (cc % 10000000000000000) / 1000000000000000;

    // Apply the Luhn Algorithm

    // Multiply every other digit by 2, starting with the number's second-to-last digit
    long second_2 = second * 2;
    long fourth_2 = fourth * 2;
    long sixth_2 = sixth * 2;
    long eighth_2 = eighth * 2;
    long tenth_2 = tenth * 2;
    long twelfth_2 = twelfth * 2;
    long fourteenth_2 = fourteenth * 2;
    long sixteenth_2 = sixteenth * 2;

    // Derive the digits, not just the number
    long second_2_1 = second_2 % 10;
    long second_2_2 = (second_2 % 100) / 10;

    long fourth_2_1 = fourth_2 % 10;
    long fourth_2_2 = (fourth_2 % 100) / 10;

    long sixth_2_1 = sixth_2 % 10;
    long sixth_2_2 = (sixth_2 % 100) / 10;

    long eighth_2_1 = eighth_2 % 10;
    long eighth_2_2 = (eighth_2 % 100) / 10;

    long tenth_2_1 = tenth_2 % 10;
    long tenth_2_2 = (tenth_2 % 100) / 10;

    long twelfth_2_1 = twelfth_2 % 10;
    long twelfth_2_2 = (twelfth_2 % 100) / 10;

    long fourteenth_2_1 = fourteenth_2 % 10;
    long fourteenth_2_2 = (fourteenth_2 % 100) / 10;

    long sixteenth_2_1 = sixteenth_2 % 10;
    long sixteenth_2_2 = (sixteenth_2 % 100) / 10;

    // Add those products' digits together
    long sum_1 = second_2_1 + second_2_2 + fourth_2_1 + fourth_2_2 + sixth_2_1 + sixth_2_2 + eighth_2_1 + eighth_2_2 + tenth_2_1 +
                 tenth_2_2 + twelfth_2_1 + twelfth_2_2 + fourteenth_2_1 + fourteenth_2_2 + sixteenth_2_1 + sixteenth_2_2;

    // Add the sum to the sum of the digits that weren't multiplied by 2
    long sum_2 = sum_1 + first + third + fifth + seventh + ninth + eleventh + thirteenth + fifteenth;

    int valid;

    // If the total's last digit is 0, the number is valid!
    if (sum_2 % 10 == 0)
    {
        valid = 1;
    }
    else
    {
        valid = 0;
    }

    // Store the length of the credit card number
    long cc_length = calculate_length(cc);

    // Check card number against criteria for each card
    if (cc_length == 15 && fifteenth == 3 && fourteenth == 4 && valid == 1)
    {
        printf("AMEX\n");
    }
    else if (cc_length == 15 && fifteenth == 3 && fourteenth == 7 && valid == 1)
    {
        printf("AMEX\n");
    }
    else if (cc_length == 16 && sixteenth == 5 && fifteenth == 1 && valid == 1)
    {
        printf("MASTERCARD\n");
    }
    else if (cc_length == 16 && sixteenth == 5 && fifteenth == 2 && valid == 1)
    {
        printf("MASTERCARD\n");
    }
    else if (cc_length == 16 && sixteenth == 5 && fifteenth == 3 && valid == 1)
    {
        printf("MASTERCARD\n");
    }
    else if (cc_length == 16 && sixteenth == 5 && fifteenth == 4 && valid == 1)
    {
        printf("MASTERCARD\n");
    }
    else if (cc_length == 16 && sixteenth == 5 && fifteenth == 5 && valid == 1)
    {
        printf("MASTERCARD\n");
    }
    else if (cc_length == 13 && thirteenth == 4 && valid == 1)
    {
        printf("VISA\n");
    }
    else if (cc_length == 16 && sixteenth == 4 && valid == 1)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

}

// Calculate the length of the user's credit card number
long calculate_length(long cc)
{
    long divisor = 1;
    long length = 0;
    while (cc / divisor != 0)
    {
        divisor *= 10;
        length += 1;
    }
    return length;
}
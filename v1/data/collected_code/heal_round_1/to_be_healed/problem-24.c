#include <stdio.h>

int binaryToDecimal(int binary)
{
    int decimal = 0, base = 1;

    while (binary > 0)
    {
        int lastDigit = binary % 10;
        binary /= 10;

        decimal += lastDigit * base;
        base *= 2;
    }

    return decimal;
}

int main()
{
    int binary;

    printf("Enter a binary number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'binary' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &binary);

    int decimal = binaryToDecimal(binary);
    printf("Decimal equivalent: %d\n", decimal);

    return 0;
}
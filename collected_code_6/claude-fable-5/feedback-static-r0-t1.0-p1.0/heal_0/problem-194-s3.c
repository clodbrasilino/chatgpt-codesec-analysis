#include <stdio.h>
#include <limits.h>

int octal_to_decimal(long octal, int *error)
{
    long decimal = 0;
    long base = 1;

    *error = 0;

    if (octal < 0) {
        *error = 1;
        return 0;
    }

    while (octal > 0) {
        long digit = octal % 10;

        if (digit > 7) {
            *error = 1;
            return 0;
        }

        if (digit != 0 && base > (LONG_MAX - decimal) / digit) {
            *error = 1;
            return 0;
        }

        decimal += digit * base;

        if (base > LONG_MAX / 8) {
            octal /= 10;
            if (octal > 0) {
                *error = 1;
                return 0;
            }
            break;
        }

        base *= 8;
        octal /= 10;
    }

    if (decimal > INT_MAX) {
        *error = 1;
        return 0;
    }

    return (int)decimal;
}

int main(void)
{
    long octal;
    int error;
    int decimal;

    printf("Enter an octal number: ");

    if (scanf("%ld", &octal) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    decimal = octal_to_decimal(octal, &error);

    if (error != 0) {
        fprintf(stderr, "Invalid octal number or overflow\n");
        return 1;
    }

    printf("Decimal equivalent: %d\n", decimal);

    return 0;
}
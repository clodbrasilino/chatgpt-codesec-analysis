#include <stdio.h>
#include <stdlib.h>

long long decimal_to_octal(long long decimal)
{
    long long octal = 0;
    long long place = 1;
    int negative = 0;

    if (decimal < 0) {
        negative = 1;
        decimal = -decimal;
    }

    if (decimal == 0) {
        return 0;
    }

    while (decimal > 0) {
        octal += (decimal % 8) * place;
        decimal /= 8;
        place *= 10;
    }

    return negative ? -octal : octal;
}

int main(void)
{
    long long decimal;
    long long octal;
    int result;

    printf("Enter a decimal number: ");
    result = scanf("%lld", &decimal);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (decimal > 999999 || decimal < -999999) {
        fprintf(stderr, "Error: input out of supported range\n");
        return EXIT_FAILURE;
    }

    octal = decimal_to_octal(decimal);
    printf("Octal equivalent: %lld\n", octal);

    return EXIT_SUCCESS;
}
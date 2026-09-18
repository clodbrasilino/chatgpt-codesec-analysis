#include <stdio.h>
#include <stdlib.h>

unsigned int count_digits(long long int number) {
    unsigned int count = 0;
    unsigned long long int unumber;

    if (number == 0) {
        return 1;
    }

    if (number < 0) {
        unumber = -(unsigned long long int)number;
    } else {
        unumber = (unsigned long long int)number;
    }

    while (unumber > 0) {
        unumber /= 10;
        count++;
    }

    return count;
}

int main(void) {
    long long int num = 0;
    unsigned int digits = 0;
    int items_read = 0;

    items_read = scanf("%lld", &num);

    if (items_read != 1) {
        return EXIT_FAILURE;
    }

    digits = count_digits(num);

    printf("%u\n", digits);

    return EXIT_SUCCESS;
}
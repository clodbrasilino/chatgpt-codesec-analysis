#include <stdio.h>
#include <stdlib.h>

unsigned int count_digits(long long int number) {
    unsigned int count = 0;

    if (number == 0) {
        return 1;
    }

    if (number < 0) {
        /* Possible weaknesses found:
         * UBSan: negation of -9223372036854775808 cannot be represented in type 'long long'; cast to an unsigned type to negate this value to itself (AFL crash: id:000000,sig:06,src:000009,time:13959,execs:5710,op:havoc,rep:4)
         */
        number = -number;
    }

    while (number > 0) {
        number /= 10;
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
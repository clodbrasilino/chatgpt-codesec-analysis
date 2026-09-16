#include <stdio.h>
#include <stdlib.h>

int count_digits(long long number);

int count_digits(long long number) {
    int count = 0;

    if (number == 0) {
        return 1;
    }

    while (number != 0) {
        count++;
        number /= 10;
    }

    return count;
}

int main(void) {
    long long num;

    if (scanf("%lld", &num) != 1) {
        return EXIT_FAILURE;
    }

    int digits = count_digits(num);

    printf("%d\n", digits);

    return EXIT_SUCCESS;
}
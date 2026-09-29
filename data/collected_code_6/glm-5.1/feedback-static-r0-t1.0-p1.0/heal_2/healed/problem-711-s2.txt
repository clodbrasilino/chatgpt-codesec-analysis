#include <stdio.h>
#include <stdlib.h>

int check_product_equality(long long n) {
    if (n < 0) {
        n = -n;
    }

    if (n < 10) {
        return n > 0 ? 1 : 0;
    }

    long long even_product = 1;
    long long odd_product = 1;
    int position = 0;

    while (n > 0) {
        int digit = n % 10;
        n /= 10;

        if (position % 2 == 0) {
            even_product *= digit;
        } else {
            odd_product *= digit;
        }
        position++;
    }

    if (even_product == odd_product) {
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, const char * const argv[]) {
    long long number;

    if (argc == 2) {
        number = atoll(argv[1]);
    } else {
        if (scanf("%lld", &number) != 1) {
            return EXIT_FAILURE;
        }
    }

    int result = check_product_equality(number);

    printf("%d\n", result);

    return EXIT_SUCCESS;
}
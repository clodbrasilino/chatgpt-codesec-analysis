#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

long long sum_of_digits_of_power(int base, int exponent) {
    if (base < 0 || exponent < 0) {
        return -1;
    }

    mpz_t num;
    mpz_init(num);

    if (base == 0 && exponent == 0) {
        mpz_set_ui(num, 1);
    } else {
        mpz_set_ui(num, base);
        mpz_pow_ui(num, num, (unsigned long)exponent);
    }

    char *str = mpz_get_str(NULL, 10, num);
    if (str == NULL) {
        mpz_clear(num);
        return -1;
    }

    long long sum = 0;
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            sum += str[i] - '0';
        }
    }

    void (*free_func)(void *, size_t);
    mp_get_memory_functions(NULL, NULL, &free_func);
    free_func(str, len + 1);

    mpz_clear(num);

    return sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return 1;
    }

    int base = atoi(argv[1]);
    int exponent = atoi(argv[2]);

    if ((base == 0 && exponent == 0) || base < 0 || exponent < 0) {
        return 1;
    }

    long long result = sum_of_digits_of_power(base, exponent);
    if (result < 0) {
        return 1;
    }

    printf("%lld\n", result);

    return 0;
}
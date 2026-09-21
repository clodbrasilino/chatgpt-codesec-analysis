#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Possible weaknesses found:
 *  gmp.h: No such file or directory
 */
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
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            sum += str[i] - '0';
        }
    }

    void (*free_func)(void *, size_t);
    mp_get_memory_functions(NULL, NULL, &free_func);
    free_func(str, mpz_sizeinbase(num, 10) + 2);

    mpz_clear(num);

    return sum;
}

long long safe_strtoll(const char *str, long long min, long long max, int *success) {
    char *endptr;
    long long val = strtoll(str, &endptr, 10);
    if (endptr == str || *endptr != '\0' || val < min || val > max) {
        *success = 0;
        return 0;
    }
    *success = 1;
    return val;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return 1;
    }

    int success;
    long long base_ll = safe_strtoll(argv[1], 0, 2147483647, &success);
    if (!success) return 1;
    
    long long exponent_ll = safe_strtoll(argv[2], 0, 2147483647, &success);
    if (!success) return 1;

    int base = (int)base_ll;
    int exponent = (int)exponent_ll;

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
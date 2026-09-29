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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    for (size_t i = 0; i < strlen(str); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            sum += str[i] - '0';
        }
    }

    void (*free_func)(void *, size_t);
    mp_get_memory_functions(NULL, NULL, &free_func);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    free_func(str, strlen(str) + 1);

    mpz_clear(num);

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int base = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
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
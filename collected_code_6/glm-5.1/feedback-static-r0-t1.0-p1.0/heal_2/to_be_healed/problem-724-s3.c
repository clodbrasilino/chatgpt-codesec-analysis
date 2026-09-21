#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* Possible weaknesses found:
 *  gmp.h: No such file or directory
 */
#include <gmp.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

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
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (isdigit((unsigned char)str[i])) {
            sum += str[i] - '0';
        }
    }

    void (*free_func)(void *, size_t);
    mp_get_memory_functions(NULL, NULL, &free_func);
    free_func(str, len + 1);

    mpz_clear(num);

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return 1;
    }

    char *endptr1;
    long base_long = strtol(argv[1], &endptr1, 10);
    /* Possible weaknesses found:
     *  Assuming that condition 'base_long<0' is not redundant
     */
    if (*endptr1 != '\0' || errno == ERANGE || base_long < 0 || base_long > INT_MAX) {
        return 1;
    }

    char *endptr2;
    long exponent_long = strtol(argv[2], &endptr2, 10);
    /* Possible weaknesses found:
     *  Assuming condition is false
     *  Assuming that condition 'exponent_long<0' is not redundant
     */
    if (*endptr2 != '\0' || errno == ERANGE || exponent_long < 0 || exponent_long > INT_MAX) {
        return 1;
    }

    /* Possible weaknesses found:
     *  Assignment 'base=(int)base_long', assigned value is greater than -1
     */
    int base = (int)base_long;
    /* Possible weaknesses found:
     *  Assignment 'exponent=(int)exponent_long', assigned value is greater than -1
     */
    int exponent = (int)exponent_long;

    /* Possible weaknesses found:
     *  Condition 'exponent<0' is always false
     *  Condition 'base<0' is always false
     *  Condition 'exponent<0' is always false [knownConditionTrueFalse]
     *  Condition 'base<0' is always false [knownConditionTrueFalse]
     */
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
#include <stdio.h>
#include <string.h>
#include <limits.h>

int octal_to_decimal(const char *octal, long *result)
{
    size_t len;
    size_t i;
    long value = 0;

    if (octal == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(octal);
    if (len == 0) {
        return -1;
    }

    for (i = 0; i < len; i++) {
        char c = octal[i];
        if (c < '0' || c > '7') {
            return -1;
        }
        if (value > (LONG_MAX - (c - '0')) / 8) {
            return -1;
        }
        value = value * 8 + (c - '0');
    }

    *result = value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    long decimal = 0;

    printf("Enter an octal number: ");

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     */
    if (scanf("%63s", input) != 1) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    if (octal_to_decimal(input, &decimal) != 0) {
        fprintf(stderr, "Error: invalid octal number or value out of range.\n");
        return 1;
    }

    printf("Decimal value: %ld\n", decimal);

    return 0;
}
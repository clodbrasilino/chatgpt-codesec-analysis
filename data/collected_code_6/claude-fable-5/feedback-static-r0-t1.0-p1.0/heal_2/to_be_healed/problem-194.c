#include <stdio.h>
#include <string.h>
#include <limits.h>

#define INPUT_SIZE 64

int octal_to_decimal(const char *octal, size_t max_len, long *result)
{
    size_t len;
    size_t i;
    long value = 0;

    if (octal == NULL || result == NULL) {
        return -1;
    }

    len = strnlen(octal, max_len);
    if (len == 0 || len == max_len) {
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
    char input[INPUT_SIZE];
    long decimal = 0;
    size_t len;

    printf("Enter an octal number: ");
    fflush(stdout);

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Error: input too long.\n");
        return 1;
    }

    if (octal_to_decimal(input, sizeof(input), &decimal) != 0) {
        fprintf(stderr, "Error: invalid octal number or value out of range.\n");
        return 1;
    }

    printf("Decimal value: %ld\n", decimal);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <limits.h>

int binary_to_decimal(const char *binary, unsigned long *result)
{
    size_t len;
    size_t i;
    unsigned long value = 0UL;

    if (binary == NULL || result == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(binary);
    if (len == 0U || len > (sizeof(unsigned long) * 8U)) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            return -1;
        }
        if (value > (ULONG_MAX >> 1)) {
            return -1;
        }
        value = (value << 1) | (unsigned long)(binary[i] - '0');
    }

    *result = value;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    unsigned long decimal = 0UL;
    size_t len;

    printf("Enter a binary number: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    }

    if (binary_to_decimal(input, &decimal) != 0) {
        fprintf(stderr, "Error: invalid binary number.\n");
        return 1;
    }

    printf("Decimal equivalent: %lu\n", decimal);
    return 0;
}
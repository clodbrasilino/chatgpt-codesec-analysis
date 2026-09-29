#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_BINARY_DIGITS 63

static bool is_valid_binary(const char *binary_str)
{
    size_t i;
    size_t len;

    if (binary_str == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(binary_str);
    if (len == 0 || len > MAX_BINARY_DIGITS) {
        return false;
    }

    for (i = 0; i < len; i++) {
        if (binary_str[i] != '0' && binary_str[i] != '1') {
            return false;
        }
    }

    return true;
}

static bool binary_to_decimal(const char *binary_str, unsigned long long *result)
{
    unsigned long long value = 0;
    size_t i;
    size_t len;

    if (!is_valid_binary(binary_str) || result == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(binary_str);

    for (i = 0; i < len; i++) {
        if (value > (ULLONG_MAX >> 1)) {
            return false;
        }
        value <<= 1;
        if (binary_str[i] == '1') {
            value |= 1;
        }
    }

    *result = value;
    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary_input[MAX_BINARY_DIGITS + 2];
    unsigned long long decimal_result;
    int scan_result;

    printf("Enter a binary number (up to %d bits): ", MAX_BINARY_DIGITS);

    /* Possible weaknesses found:
     * Flawfinder scanf: It's unclear if the %s limit in the format string is small enough (CWE-120). Check that the limit is sufficiently small, or use a different input function. (risk 1, buffer)
     *  Width 65 given in format string (no. 1) is larger than destination buffer 'binary_input[65]', use %64s to prevent overflowing it. [invalidScanfFormatWidth]
     */
    scan_result = scanf("%65s", binary_input);
    if (scan_result != 1) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return 1;
    }

    if (binary_to_decimal(binary_input, &decimal_result)) {
        printf("Decimal equivalent: %llu\n", decimal_result);
    } else {
        fprintf(stderr, "Error: Invalid binary number or overflow.\n");
        return 1;
    }

    return 0;
}
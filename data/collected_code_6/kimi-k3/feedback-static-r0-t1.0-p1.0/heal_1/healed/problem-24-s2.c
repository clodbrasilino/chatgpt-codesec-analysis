#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_BINARY_DIGITS 63

static bool is_valid_binary(const char *binary_str, size_t max_len)
{
    size_t i;
    size_t len = 0;

    if (binary_str == NULL) {
        return false;
    }

    while (len < max_len && binary_str[len] != '\0') {
        len++;
    }

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

static bool binary_to_decimal(const char *binary_str, size_t max_len, unsigned long long *result)
{
    unsigned long long value = 0;
    size_t i;
    size_t len = 0;

    if (!is_valid_binary(binary_str, max_len) || result == NULL) {
        return false;
    }

    while (len < max_len && binary_str[len] != '\0') {
        len++;
    }

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
    char binary_input[MAX_BINARY_DIGITS + 2];
    unsigned long long decimal_result;
    int scan_result;

    printf("Enter a binary number (up to %d bits): ", MAX_BINARY_DIGITS);

    scan_result = scanf("%64s", binary_input);
    if (scan_result != 1) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return 1;
    }

    if (binary_to_decimal(binary_input, sizeof(binary_input), &decimal_result)) {
        printf("Decimal equivalent: %llu\n", decimal_result);
    } else {
        fprintf(stderr, "Error: Invalid binary number or overflow.\n");
        return 1;
    }

    return 0;
}
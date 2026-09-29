#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_BINARY_DIGITS 63
#define INPUT_BUFFER_SIZE (MAX_BINARY_DIGITS + 2)

static bool is_valid_binary(const char *binary_str, size_t max_len)
{
    size_t i;
    size_t len;

    if (binary_str == NULL) {
        return false;
    }

    len = strnlen(binary_str, max_len);
    if (len == 0 || len >= max_len || len > MAX_BINARY_DIGITS) {
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
    size_t len;

    if (result == NULL || !is_valid_binary(binary_str, max_len)) {
        return false;
    }

    len = strnlen(binary_str, max_len);

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

static void clear_stdin_line(void)
{
    int ch;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char binary_input[INPUT_BUFFER_SIZE];
    unsigned long long decimal_result;
    size_t input_len;

    printf("Enter a binary number (up to %d bits): ", MAX_BINARY_DIGITS);

    if (fgets(binary_input, sizeof(binary_input), stdin) == NULL) {
        fprintf(stderr, "Error: Failed to read input.\n");
        return 1;
    }

    input_len = strnlen(binary_input, sizeof(binary_input));
    if (input_len > 0 && binary_input[input_len - 1] == '\n') {
        binary_input[input_len - 1] = '\0';
    } else if (input_len == sizeof(binary_input) - 1) {
        clear_stdin_line();
    }

    if (binary_to_decimal(binary_input, sizeof(binary_input), &decimal_result)) {
        printf("Decimal equivalent: %llu\n", decimal_result);
    } else {
        fprintf(stderr, "Error: Invalid binary number or overflow.\n");
        return 1;
    }

    return 0;
}
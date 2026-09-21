#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stddef.h>

#define INPUT_BUFFER_SIZE 128U
#define MAX_BINARY_DIGITS (sizeof(unsigned long) * 8U)

int binary_to_decimal(const char *binary, size_t max_len, unsigned long *result)
{
    size_t len;
    size_t i;
    unsigned long value = 0UL;

    if (binary == NULL || result == NULL || max_len == 0U) {
        return -1;
    }

    len = strnlen(binary, max_len);
    if (len == 0U || len >= max_len || len > MAX_BINARY_DIGITS) {
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
    char input[INPUT_BUFFER_SIZE];
    unsigned long decimal = 0UL;
    size_t len;

    printf("Enter a binary number: ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    input[sizeof(input) - 1U] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    }

    if (binary_to_decimal(input, sizeof(input), &decimal) != 0) {
        fprintf(stderr, "Error: invalid binary number.\n");
        return 1;
    }

    printf("Decimal equivalent: %lu\n", decimal);
    return 0;
}
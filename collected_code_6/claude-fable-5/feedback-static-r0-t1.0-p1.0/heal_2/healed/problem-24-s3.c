#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_BINARY_DIGITS 64
#define INPUT_BUFFER_SIZE 128

static int binary_to_decimal(const char *binary, size_t max_len, unsigned long *result)
{
    size_t len;
    size_t i;
    unsigned long value;

    if (binary == NULL || result == NULL) {
        return -1;
    }

    len = strnlen(binary, max_len);
    if (len == 0 || len >= max_len || len > MAX_BINARY_DIGITS) {
        return -1;
    }

    value = 0;
    for (i = 0; i < len; i++) {
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
    unsigned long decimal;
    size_t len;

    memset(input, 0, sizeof(input));

    printf("Enter a binary number: ");
    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        fprintf(stderr, "Error: input too long\n");
        return EXIT_FAILURE;
    }

    if (binary_to_decimal(input, sizeof(input), &decimal) != 0) {
        fprintf(stderr, "Error: invalid binary number\n");
        return EXIT_FAILURE;
    }

    printf("Decimal equivalent: %lu\n", decimal);
    return EXIT_SUCCESS;
}
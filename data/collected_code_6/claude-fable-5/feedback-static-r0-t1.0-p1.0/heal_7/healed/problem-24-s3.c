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

    if (binary == NULL || result == NULL || max_len == 0) {
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

static void discard_remaining_input(void)
{
    size_t guard = 0;

    while (guard < (size_t)INT_MAX) {
        int ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        }
        guard++;
    }
}

static int read_line(char *buffer, size_t size)
{
    size_t len;

    if (buffer == NULL || size < 2 || size > (size_t)INT_MAX) {
        return -1;
    }

    memset(buffer, 0, size);

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    buffer[size - 1] = '\0';

    len = strnlen(buffer, size);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        return 0;
    }

    if (len == size - 1) {
        discard_remaining_input();
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[INPUT_BUFFER_SIZE];
    unsigned long decimal;

    printf("Enter a binary number: ");
    if (fflush(stdout) != 0) {
        return EXIT_FAILURE;
    }

    if (read_line(input, sizeof(input)) != 0) {
        fprintf(stderr, "Error: failed to read input or input too long\n");
        return EXIT_FAILURE;
    }

    if (binary_to_decimal(input, sizeof(input), &decimal) != 0) {
        fprintf(stderr, "Error: invalid binary number\n");
        return EXIT_FAILURE;
    }

    printf("Decimal equivalent: %lu\n", decimal);
    return EXIT_SUCCESS;
}
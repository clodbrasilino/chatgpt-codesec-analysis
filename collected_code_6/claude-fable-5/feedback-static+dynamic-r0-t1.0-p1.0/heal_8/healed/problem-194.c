#include <stdio.h>
#include <string.h>
#include <limits.h>

#define INPUT_SIZE 64
#define FLUSH_LIMIT 4096

int octal_to_decimal(const char *octal, size_t max_len, long *result)
{
    size_t len;
    size_t i;
    long value = 0;

    if (octal == NULL || result == NULL || max_len == 0) {
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
        if (value > (LONG_MAX - (long)(c - '0')) / 8) {
            return -1;
        }
        value = value * 8 + (long)(c - '0');
    }

    *result = value;
    return 0;
}

static void flush_stdin(void)
{
    int ch;
    size_t count = 0;

    do {
        ch = getchar();
        count++;
    } while (ch != '\n' && ch != EOF && count < FLUSH_LIMIT);
}

int main(void)
{
    char input[INPUT_SIZE] = {0};
    long decimal = 0;
    size_t len;

    printf("Enter an octal number: ");
    fflush(stdout);

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return 1;
    }

    input[sizeof(input) - 1] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    } else if (len == sizeof(input) - 1) {
        flush_stdin();
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
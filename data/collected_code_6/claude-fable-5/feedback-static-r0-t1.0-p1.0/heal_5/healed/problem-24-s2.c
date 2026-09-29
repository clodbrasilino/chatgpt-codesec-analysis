#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_INPUT_LEN 128U

static int binary_to_decimal(const char *binary, unsigned long long *result)
{
    size_t len;
    size_t i;
    unsigned long long value = 0ULL;

    if (binary == NULL || result == NULL) {
        return -1;
    }

    len = strnlen(binary, MAX_INPUT_LEN);
    if (len == 0U || len >= MAX_INPUT_LEN) {
        return -1;
    }

    for (i = 0U; i < len; i++) {
        if (binary[i] != '0' && binary[i] != '1') {
            return -1;
        }
        if (value > (ULLONG_MAX >> 1)) {
            return -1;
        }
        value = (value << 1) | (unsigned long long)(binary[i] - '0');
    }

    *result = value;
    return 0;
}

static int flush_stdin_check_truncation(void)
{
    int ch;
    int truncated = 0;
    unsigned long guard = 0UL;

    do {
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        }
        truncated = 1;
        guard++;
    } while (guard < ULONG_MAX);

    return truncated;
}

int main(void)
{
    char input[MAX_INPUT_LEN];
    unsigned long long decimal = 0ULL;
    size_t len;

    memset(input, 0, sizeof(input));

    printf("Enter a binary number: ");

    if (fgets(input, (int)sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    input[sizeof(input) - 1U] = '\0';

    len = strnlen(input, sizeof(input));
    if (len > 0U && input[len - 1U] == '\n') {
        input[len - 1U] = '\0';
    } else {
        if (flush_stdin_check_truncation() == 1) {
            fprintf(stderr, "Error: input too long.\n");
            return EXIT_FAILURE;
        }
    }

    if (binary_to_decimal(input, &decimal) != 0) {
        fprintf(stderr, "Error: invalid binary number.\n");
        return EXIT_FAILURE;
    }

    printf("Decimal equivalent: %llu\n", decimal);
    return EXIT_SUCCESS;
}
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define INPUT_CAPACITY 4096U

static int count_substrings(const char *str, uint64_t *result)
{
    uint64_t frequencies[UCHAR_MAX + 1U] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; str[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)str[i];

        if (frequencies[c] == UINT64_MAX ||
            total > UINT64_MAX - frequencies[c] - 1U) {
            return -1;
        }

        total += frequencies[c] + 1U;
        ++frequencies[c];
    }

    *result = total;
    return 0;
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length = 0;
    uint64_t result;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length + 1U >= sizeof input) {
            while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
            }
            return 1;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (ch == EOF && length == 0U) {
        return 1;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    input[length] = '\0';

    if (count_substrings(input, &result) != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}
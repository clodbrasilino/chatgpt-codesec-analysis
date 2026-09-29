#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static int count_substrings(const char *str, uint64_t *result)
{
    uint64_t frequencies[256] = {0};
    uint64_t total = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; str[i] != '\0'; ++i) {
        unsigned char c = (unsigned char)str[i];

        if (UINT64_MAX - total <= frequencies[c]) {
            return -1;
        }

        total += frequencies[c] + 1;
        ++frequencies[c];
    }

    *result = total;
    return 0;
}

int main(void)
{
    char input[4096];
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
        if (length > 0 && input[length - 1] == '\r') {
            input[length - 1] = '\0';
        }
    } else if (!feof(stdin)) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        return 1;
    }

    if (count_substrings(input, &result) != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}
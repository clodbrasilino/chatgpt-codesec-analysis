#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

static int count_non_empty_substrings(const char *str, uint64_t *count)
{
    if (str == NULL || count == NULL) {
        return -1;
    }

    size_t length = strlen(str);
    uint64_t n = (uint64_t)length;

    if (length != (size_t)n) {
        return -1;
    }

    if ((n & 1U) == 0U) {
        n /= 2U;
    } else {
        if (n == UINT64_MAX) {
            return -1;
        }
        n = (n + 1U) / 2U;
    }

    uint64_t factor = ((uint64_t)length & 1U) == 0U
                          ? (uint64_t)length + 1U
                          : (uint64_t)length;

    if (factor != 0U && n > UINT64_MAX / factor) {
        return -1;
    }

    *count = n * factor;
    return 0;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[length - 1U] = '\0';
    } else if (!feof(stdin)) {
        int ch;
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return 1;
    }

    uint64_t count;

    if (count_non_empty_substrings(input, &count) != 0) {
        return 1;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return 1;
    }

    return 0;
}
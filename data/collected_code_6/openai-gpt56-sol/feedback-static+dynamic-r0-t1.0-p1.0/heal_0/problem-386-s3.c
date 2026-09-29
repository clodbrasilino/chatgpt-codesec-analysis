#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int minimum_swaps(const char *str, size_t *result)
{
    size_t length;
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (str == NULL || result == NULL) {
        return 0;
    }

    length = strlen(str);

    for (size_t i = 0; i < length; ++i) {
        if (str[i] == '[') {
            ++open_count;

            if (imbalance > 0) {
                swaps += imbalance;
                --imbalance;
            }
        } else if (str[i] == ']') {
            ++close_count;
            imbalance = close_count - open_count;
        } else {
            return 0;
        }
    }

    if (open_count != close_count) {
        return 0;
    }

    *result = swaps;
    return 1;
}

int main(void)
{
    char input[1000001];
    size_t swaps;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    size_t length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';
    } else if (length == sizeof(input) - 1) {
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return EXIT_FAILURE;
        }
    }

    if (length > 0 && input[length - 1] == '\r') {
        input[length - 1] = '\0';
    }

    if (!minimum_swaps(input, &swaps)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", swaps) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
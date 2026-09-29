#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int minimum_swaps(const char *str, size_t *result)
{
    size_t open_count = 0;
    size_t close_count = 0;
    size_t imbalance = 0;
    size_t swaps = 0;

    if (str == NULL || result == NULL) {
        return -1;
    }

    for (const char *p = str; *p != '\0'; ++p) {
        if (*p == '[') {
            ++open_count;
            if (imbalance > 0) {
                if (swaps > SIZE_MAX - imbalance) {
                    return -1;
                }
                swaps += imbalance;
                --imbalance;
            }
        } else if (*p == ']') {
            ++close_count;
            if (close_count > open_count) {
                imbalance = close_count - open_count;
            }
        } else {
            return -1;
        }
    }

    if (open_count != close_count) {
        return -1;
    }

    *result = swaps;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    size_t swaps;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (minimum_swaps(input, &swaps) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", swaps) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}
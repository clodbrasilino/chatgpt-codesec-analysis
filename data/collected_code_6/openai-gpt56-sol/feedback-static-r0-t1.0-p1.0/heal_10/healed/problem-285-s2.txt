#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    static const char pattern1[] = "abb";
    static const char pattern2[] = "abbb";

    if (string == NULL) {
        return false;
    }

    return (length == sizeof(pattern1) - 1U &&
            memcmp(string, pattern1, sizeof(pattern1) - 1U) == 0) ||
           (length == sizeof(pattern2) - 1U &&
            memcmp(string, pattern2, sizeof(pattern2) - 1U) == 0);
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;
    bool allocation_failed = false;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 16U : capacity * 2U;
            char *resized;

            if (new_capacity <= capacity) {
                allocation_failed = true;
                break;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                allocation_failed = true;
                break;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (allocation_failed || ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        size_t new_capacity = capacity == 0U ? 1U : capacity + 1U;
        char *resized;

        if (new_capacity <= capacity) {
            free(input);
            return EXIT_FAILURE;
        }

        resized = realloc(input, new_capacity);
        if (resized == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';

    if (puts(matches_pattern(input, length) ? "Match" : "No match") == EOF) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}
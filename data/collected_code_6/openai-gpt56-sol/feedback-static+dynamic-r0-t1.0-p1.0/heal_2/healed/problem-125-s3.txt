#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

static int maximum_difference(const char *str, int *result)
{
    if (str == NULL || result == NULL || *str == '\0') {
        return 0;
    }

    int current = 0;
    int maximum = INT_MIN;

    for (const char *p = str; *p != '\0'; ++p) {
        int value;

        if (*p == '0') {
            value = 1;
        } else if (*p == '1') {
            value = -1;
        } else {
            return 0;
        }

        current = current < 0 ? value : current + value;

        if (current > maximum) {
            maximum = current;
        }
    }

    *result = maximum;
    return 1;
}

static int read_input(char **buffer)
{
    if (buffer == NULL) {
        return 0;
    }

    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        return 0;
    }

    int ch;

    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        if (ch != '0' && ch != '1') {
            free(input);
            return 0;
        }

        if (length >= capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(input);
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                free(input);
                return 0;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ferror(stdin) || length == 0) {
        free(input);
        return 0;
    }

    if (ch == '\r') {
        int next = getchar();

        if (next != '\n' && next != EOF) {
            free(input);
            return 0;
        }

        if (ferror(stdin)) {
            free(input);
            return 0;
        }
    }

    input[length] = '\0';
    *buffer = input;
    return 1;
}

int main(void)
{
    char *input = NULL;

    if (!read_input(&input)) {
        return EXIT_FAILURE;
    }

    int result;

    if (!maximum_difference(input, &result)) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
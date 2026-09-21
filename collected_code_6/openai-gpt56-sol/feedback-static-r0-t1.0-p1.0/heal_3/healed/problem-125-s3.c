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

static int read_line(char **line)
{
    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    size_t capacity = 128;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    size_t length = 0;

    for (;;) {
        if (fgets(buffer + length, (int)(capacity - length), stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        while (buffer[length] != '\0' &&
               buffer[length] != '\n' &&
               buffer[length] != '\r') {
            ++length;
        }

        if (buffer[length] == '\n' || buffer[length] == '\r') {
            buffer[length] = '\0';
            break;
        }

        if (feof(stdin)) {
            break;
        }

        if (capacity > SIZE_MAX / 2 || capacity * 2 > (size_t)INT_MAX) {
            free(buffer);
            return 0;
        }

        size_t new_capacity = capacity * 2;
        char *resized = realloc(buffer, new_capacity);

        if (resized == NULL) {
            free(buffer);
            return 0;
        }

        buffer = resized;
        capacity = new_capacity;
    }

    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    int result;

    if (!read_line(&input)) {
        return EXIT_FAILURE;
    }

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
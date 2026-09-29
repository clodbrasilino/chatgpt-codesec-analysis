#include <stdio.h>
#include <stdlib.h>

static int first_and_last_equal(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           string[0] == string[length - 1U];
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 128U;
    size_t count = 0U;
    char *line;
    int character;

    if (buffer == NULL || length == NULL) {
        return 0;
    }

    *buffer = NULL;
    *length = 0U;

    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    while ((character = getchar()) != '\n' && character != EOF) {
        if (count == capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(line);
                return 0;
            }

            new_capacity = capacity * 2U;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[count++] = (char)character;
    }

    if (character == EOF && count == 0U) {
        free(line);
        return 0;
    }

    line[count] = '\0';
    *buffer = line;
    *length = count;
    return 1;
}

int main(void)
{
    char *string;
    size_t length;

    if (!read_line(&string, &length)) {
        return EXIT_FAILURE;
    }

    puts(first_and_last_equal(string, length) ? "Equal" : "Not equal");

    free(string);
    return EXIT_SUCCESS;
}
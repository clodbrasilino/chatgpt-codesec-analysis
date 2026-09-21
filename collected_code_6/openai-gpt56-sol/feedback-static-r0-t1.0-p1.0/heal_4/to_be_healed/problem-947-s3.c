#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t shortest_word_length(const char *text)
{
    size_t shortest = SIZE_MAX;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isspace((unsigned char)*text)) {
            if (current != 0 && current < shortest) {
                shortest = current;
            }
            current = 0;
        } else {
            if (current == SIZE_MAX) {
                return 0;
            }
            ++current;
        }
        ++text;
    }

    if (current != 0 && current < shortest) {
        shortest = current;
    }

    return shortest == SIZE_MAX ? 0 : shortest;
}

static int read_line(FILE *stream, char **buffer)
{
    char *data = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    if (stream == NULL || buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length > SIZE_MAX - 2) {
            free(data);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *temporary;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity <= SIZE_MAX / 2) {
                new_capacity = capacity * 2;
            } else {
                new_capacity = SIZE_MAX;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            temporary = realloc(data, new_capacity);
            if (temporary == NULL) {
                free(data);
                return 0;
            }

            data = temporary;
            capacity = new_capacity;
        }

        data[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream)) {
        free(data);
        return 0;
    }

    if (data == NULL) {
        data = malloc(1);
        if (data == NULL) {
            return 0;
        }
    }

    data[length] = '\0';
    *buffer = data;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t shortest;

    if (!read_line(stdin, &input)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    shortest = shortest_word_length(input);

    if (shortest == 0) {
        puts("No words found.");
    } else {
        printf("%zu\n", shortest);
    }

    free(input);
    return EXIT_SUCCESS;
}
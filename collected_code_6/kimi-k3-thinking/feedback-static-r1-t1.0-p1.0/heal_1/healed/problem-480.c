#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_CHARS 256

static char *read_line(FILE *stream)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int ch;

    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int find_max_occurring_char(const char *str, char *max_char, size_t *max_count)
{
    size_t counts[NUM_CHARS] = {0};
    size_t highest = 0;

    if (str == NULL || max_char == NULL || max_count == NULL) {
        return -1;
    }

    if (str[0] == '\0') {
        return -1;
    }

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];

        counts[c]++;

        if (counts[c] > highest) {
            highest = counts[c];
            *max_char = (char)c;
        }
    }

    *max_count = highest;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char max_char = '\0';
    size_t max_count = 0;

    printf("Enter a string: ");

    input = read_line(stdin);

    if (input == NULL) {
        fprintf(stderr, "Error: failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (find_max_occurring_char(input, &max_char, &max_count) != 0) {
        fprintf(stderr, "Error: invalid or empty string.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Maximum occurring character: '%c'\n", max_char);
    printf("Occurrences: %zu\n", max_count);

    free(input);
    return EXIT_SUCCESS;
}
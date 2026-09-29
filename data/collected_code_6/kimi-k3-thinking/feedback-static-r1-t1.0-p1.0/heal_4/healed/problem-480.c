#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define NUM_CHARS 256
#define INITIAL_CAPACITY 64

static char *read_line(FILE *stream)
{
    size_t capacity = INITIAL_CAPACITY;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        size_t space = capacity - length;
        size_t chunk;
        void *terminator;

        if (space < 2) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = new_buffer;
            capacity = new_capacity;
            continue;
        }

        chunk = (space > (size_t)INT_MAX) ? (size_t)INT_MAX : space;

        if (fgets(buffer + length, (int)chunk, stream) == NULL) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        terminator = memchr(buffer + length, '\0', chunk);

        if (terminator == NULL) {
            free(buffer);
            return NULL;
        }

        length += (size_t)((char *)terminator - (buffer + length));

        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
            break;
        }

        if (length < capacity - 1) {
            break;
        }
    }

    return buffer;
}

int find_max_occurring_char(const char *str, char *max_char, size_t *max_count)
{
    size_t counts[NUM_CHARS] = {0};
    size_t highest = 0;
    size_t i;

    if (str == NULL || max_char == NULL || max_count == NULL) {
        return -1;
    }

    if (str[0] == '\0') {
        return -1;
    }

    for (i = 0; str[i] != '\0'; i++) {
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
    fflush(stdout);

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
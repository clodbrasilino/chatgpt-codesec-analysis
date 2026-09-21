#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_valid_digit_frequencies(const char *input)
{
    size_t frequencies[10] = {0};

    if (input == NULL || input[0] == '\0') {
        return false;
    }

    for (const unsigned char *p = (const unsigned char *)input; *p != '\0'; ++p) {
        if (*p < (unsigned char)'0' || *p > (unsigned char)'9') {
            return false;
        }

        size_t digit = (size_t)(*p - (unsigned char)'0');

        if (frequencies[digit] >= digit) {
            return false;
        }

        ++frequencies[digit];
    }

    return true;
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return NULL;
    }

    while (fgets(buffer + length, (int)(capacity - length), stream) != NULL) {
        length += strlen(buffer + length);

        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[--length] = '\0';
            return buffer;
        }

        if (feof(stream)) {
            return buffer;
        }

        if (capacity > SIZE_MAX / 2) {
            free(buffer);
            return NULL;
        }

        size_t new_capacity = capacity * 2;

        if (new_capacity > (size_t)INT_MAX) {
            new_capacity = (size_t)INT_MAX;
        }

        if (new_capacity <= capacity) {
            free(buffer);
            return NULL;
        }

        char *new_buffer = realloc(buffer, new_capacity);

        if (new_buffer == NULL) {
            free(buffer);
            return NULL;
        }

        buffer = new_buffer;
        capacity = new_capacity;
    }

    if (ferror(stream) || length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_valid_digit_frequencies(input) ? "true" : "false");
    free(input);

    return EXIT_SUCCESS;
}
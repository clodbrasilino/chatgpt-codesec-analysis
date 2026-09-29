#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *start;
    size_t length;
} WordView;

static bool find_first_maximum_even_word(const char *text, WordView *result)
{
    const char *current;
    size_t maximum_length = 0;

    if (text == NULL || result == NULL) {
        return false;
    }

    result->start = NULL;
    result->length = 0;
    current = text;

    while (*current != '\0') {
        const char *word_start;
        size_t word_length = 0;

        while (*current != '\0' &&
               isspace((unsigned char)*current) != 0) {
            ++current;
        }

        word_start = current;

        while (*current != '\0' &&
               isspace((unsigned char)*current) == 0) {
            ++current;
            ++word_length;
        }

        if (word_length != 0 &&
            word_length % 2 == 0 &&
            word_length > maximum_length) {
            result->start = word_start;
            result->length = word_length;
            maximum_length = word_length;
        }
    }

    return result->start != NULL;
}

static bool grow_buffer(char **buffer, size_t *capacity)
{
    char *resized;
    size_t new_capacity;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return false;
    }

    if (*capacity > SIZE_MAX / 2) {
        return false;
    }

    new_capacity = *capacity * 2;
    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return false;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return true;
}

static bool read_input(char **buffer)
{
    size_t capacity = 256;
    size_t length = 0;
    char *data;

    if (buffer == NULL) {
        return false;
    }

    *buffer = NULL;

    data = malloc(capacity);
    if (data == NULL) {
        return false;
    }

    for (;;) {
        size_t available;
        size_t bytes_read;

        if (length == capacity - 1) {
            if (!grow_buffer(&data, &capacity)) {
                free(data);
                return false;
            }
        }

        available = capacity - length - 1;
        bytes_read = fread(data + length, 1, available, stdin);
        length += bytes_read;

        if (bytes_read < available) {
            if (ferror(stdin)) {
                free(data);
                return false;
            }

            if (feof(stdin)) {
                break;
            }

            if (bytes_read == 0) {
                free(data);
                return false;
            }
        }
    }

    data[length] = '\0';
    *buffer = data;
    return true;
}

int main(void)
{
    char *input = NULL;
    WordView result;
    int status = EXIT_SUCCESS;

    if (!read_input(&input)) {
        return EXIT_FAILURE;
    }

    if (find_first_maximum_even_word(input, &result)) {
        if (fwrite(result.start, 1, result.length, stdout) != result.length ||
            fputc('\n', stdout) == EOF) {
            status = EXIT_FAILURE;
        }
    } else if (fputs("00\n", stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(input);
    return status;
}
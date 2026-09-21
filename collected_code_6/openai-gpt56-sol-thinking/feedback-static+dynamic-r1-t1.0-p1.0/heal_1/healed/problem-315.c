#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_input(char **buffer, size_t *length)
{
    size_t capacity = 256;
    size_t used = 0;
    char *data;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    for (;;) {
        size_t available;
        size_t bytes_read;

        if (used == capacity) {
            size_t new_capacity;
            char *expanded;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return -1;
            }

            new_capacity = capacity * 2;
            expanded = realloc(data, new_capacity);
            if (expanded == NULL) {
                free(data);
                return -1;
            }

            data = expanded;
            capacity = new_capacity;
        }

        available = capacity - used;
        bytes_read = fread(data + used, 1, available, stdin);
        used += bytes_read;

        if (bytes_read < available) {
            if (ferror(stdin)) {
                free(data);
                return -1;
            }

            if (feof(stdin)) {
                break;
            }

            if (bytes_read == 0) {
                free(data);
                return -1;
            }
        }
    }

    *buffer = data;
    *length = used;
    return 0;
}

static int find_first_maximum_even_word(const char *text, size_t text_length,
                                        const char **word,
                                        size_t *word_length)
{
    size_t index = 0;
    size_t maximum_length = 0;
    const char *maximum_word = NULL;

    if ((text == NULL && text_length != 0) ||
        word == NULL || word_length == NULL) {
        return -1;
    }

    *word = NULL;
    *word_length = 0;

    while (index < text_length) {
        size_t start;
        size_t current_length;

        while (index < text_length &&
               isspace((unsigned char)text[index])) {
            ++index;
        }

        start = index;

        while (index < text_length &&
               !isspace((unsigned char)text[index])) {
            ++index;
        }

        current_length = index - start;

        if (current_length != 0 &&
            current_length % 2 == 0 &&
            current_length > maximum_length) {
            maximum_word = text + start;
            maximum_length = current_length;
        }
    }

    *word = maximum_word;
    *word_length = maximum_length;

    return maximum_word != NULL;
}

int main(void)
{
    char *input = NULL;
    size_t input_length = 0;
    const char *word = NULL;
    size_t word_length = 0;
    int result;
    int status = EXIT_SUCCESS;

    if (read_input(&input, &input_length) != 0) {
        return EXIT_FAILURE;
    }

    result = find_first_maximum_even_word(input, input_length,
                                          &word, &word_length);
    if (result < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    if (result > 0 &&
        fwrite(word, 1, word_length, stdout) != word_length) {
        status = EXIT_FAILURE;
    }

    if (status == EXIT_SUCCESS && fputc('\n', stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    if (status == EXIT_SUCCESS && fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(input);
    return status;
}
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int read_input(char **buffer, size_t *length)
{
    unsigned char chunk[4096];
    char *data = NULL;
    size_t capacity = 0;
    size_t used = 0;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    for (;;) {
        size_t count = fread(chunk, 1, sizeof chunk, stdin);

        if (count > 0) {
            size_t required;

            if (count > SIZE_MAX - used) {
                free(data);
                return -1;
            }

            required = used + count;

            if (required > capacity) {
                size_t new_capacity = capacity == 0 ? sizeof chunk : capacity;
                char *expanded;

                while (new_capacity < required) {
                    if (new_capacity > SIZE_MAX / 2) {
                        new_capacity = required;
                        break;
                    }
                    new_capacity *= 2;
                }

                expanded = realloc(data, new_capacity);
                if (expanded == NULL) {
                    free(data);
                    return -1;
                }

                data = expanded;
                capacity = new_capacity;
            }

            memcpy(data + used, chunk, count);
            used = required;
        }

        if (count < sizeof chunk) {
            if (ferror(stdin)) {
                free(data);
                return -1;
            }

            if (feof(stdin)) {
                break;
            }
        }
    }

    *buffer = data;
    *length = used;
    return 0;
}

static int find_first_maximum_even_word(const char *text, size_t text_length,
                                        const char **word, size_t *word_length)
{
    size_t index = 0;
    size_t maximum_length = 0;
    const char *maximum_word = NULL;

    if ((text == NULL && text_length != 0) ||
        word == NULL ||
        word_length == NULL) {
        return -1;
    }

    while (index < text_length) {
        size_t start;
        size_t length;

        while (index < text_length &&
               isspace((unsigned char)text[index])) {
            ++index;
        }

        start = index;

        while (index < text_length &&
               !isspace((unsigned char)text[index])) {
            ++index;
        }

        length = index - start;

        if (length != 0 &&
            length % 2 == 0 &&
            length > maximum_length) {
            maximum_word = text + start;
            maximum_length = length;
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
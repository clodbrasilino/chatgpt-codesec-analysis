#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int read_input(char **buffer, size_t *length)
{
    char *data;
    size_t capacity = 256;
    size_t used = 0;
    int ch;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    data = malloc(capacity);
    if (data == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (used == capacity) {
            char *expanded;
            size_t new_capacity;

            if (capacity > (size_t)-1 / 2) {
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

        data[used++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(data);
        return -1;
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

    if ((text == NULL && text_length != 0) || word == NULL || word_length == NULL) {
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

        if (length != 0 && length % 2 == 0 && length > maximum_length) {
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

    if (result > 0 && fwrite(word, 1, word_length, stdout) != word_length) {
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
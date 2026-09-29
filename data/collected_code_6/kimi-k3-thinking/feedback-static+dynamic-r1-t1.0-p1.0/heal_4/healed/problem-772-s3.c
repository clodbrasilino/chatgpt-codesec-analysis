#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define INITIAL_INPUT_CAPACITY 128u
#define MAX_INPUT_LENGTH ((size_t)1024u * 1024u)

static char *read_line(FILE *stream, size_t max_len)
{
    size_t capacity = INITIAL_INPUT_CAPACITY;
    size_t length = 0;
    int ch;

    if (stream == NULL || max_len == 0) {
        return NULL;
    }

    char *buffer = (char *)malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        if (length >= max_len) {
            free(buffer);
            return NULL;
        }
        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            if (new_capacity > max_len && max_len < SIZE_MAX) {
                new_capacity = max_len + 1;
            }
            if (new_capacity <= capacity) {
                free(buffer);
                return NULL;
            }
            char *new_buffer = (char *)realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return NULL;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        if (length < capacity - 1) {
            buffer[length] = (char)ch;
            length++;
        } else {
            free(buffer);
            return NULL;
        }
    }

    if (ferror(stream)) {
        free(buffer);
        return NULL;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return NULL;
    }

    buffer[length] = '\0';
    return buffer;
}

char *remove_words_of_length(const char *str, size_t k, size_t str_max_len)
{
    if (str == NULL || str_max_len == 0) {
        return NULL;
    }

    size_t len = strnlen(str, str_max_len);
    size_t result_capacity = len + 1;
    char *result = (char *)malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    int first_word = 1;

    while (i < len) {
        while (i < len && isspace((unsigned char)str[i])) {
            i++;
        }
        if (i >= len) {
            break;
        }

        size_t word_start = i;
        while (i < len && !isspace((unsigned char)str[i])) {
            i++;
        }
        size_t word_len = i - word_start;

        if (word_len != k) {
            size_t prefix = first_word ? 0u : 1u;
            size_t remaining = result_capacity - j;
            if (prefix > remaining || word_len > remaining - prefix ||
                prefix + word_len >= remaining) {
                free(result);
                return NULL;
            }
            if (!first_word) {
                result[j++] = ' ';
            }
            memcpy(result + j, str + word_start, word_len);
            j += word_len;
            first_word = 0;
        }
    }
    result[j] = '\0';

    char *shrunk = (char *)realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

int main(void)
{
    size_t k = 0;

    printf("Enter a string: ");
    fflush(stdout);

    char *input = read_line(stdin, MAX_INPUT_LENGTH);
    if (input == NULL) {
        fprintf(stderr, "Error reading input.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the word length to remove: ");
    fflush(stdout);

    if (scanf("%zu", &k) != 1) {
        fprintf(stderr, "Invalid length value.\n");
        free(input);
        return EXIT_FAILURE;
    }

    size_t input_len = strnlen(input, MAX_INPUT_LENGTH + 1);
    if (input_len > MAX_INPUT_LENGTH) {
        fprintf(stderr, "Input string is not properly terminated.\n");
        free(input);
        return EXIT_FAILURE;
    }

    char *modified = remove_words_of_length(input, k, input_len + 1);
    if (modified == NULL) {
        fprintf(stderr, "Failed to process the string.\n");
        free(input);
        return EXIT_FAILURE;
    }

    printf("Result: \"%s\"\n", modified);

    free(modified);
    free(input);
    return EXIT_SUCCESS;
}
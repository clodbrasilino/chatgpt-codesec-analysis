#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *find_first_longest_even_word(const char *text)
{
    const char *word_start = NULL;
    const char *best_start = NULL;
    size_t word_length = 0;
    size_t best_length = 0;

    if (text == NULL) {
        return NULL;
    }

    for (const char *current = text;; ++current) {
        unsigned char character = (unsigned char)*current;

        if (character != '\0' && !isspace(character)) {
            if (word_start == NULL) {
                word_start = current;
            }

            if (word_length == SIZE_MAX) {
                return NULL;
            }

            ++word_length;
        } else {
            if (word_length != 0 &&
                word_length % 2 == 0 &&
                word_length > best_length) {
                best_start = word_start;
                best_length = word_length;
            }

            word_start = NULL;
            word_length = 0;

            if (character == '\0') {
                break;
            }
        }
    }

    if (best_start == NULL || best_length == SIZE_MAX) {
        return NULL;
    }

    char *result = malloc(best_length + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, best_start, best_length);
    result[best_length] = '\0';

    return result;
}

int main(void)
{
    size_t capacity = 256;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while (fgets(input + length, (int)(capacity - length), stdin) != NULL) {
        size_t bytes_read = strlen(input + length);
        length += bytes_read;

        if (length > 0 && input[length - 1] == '\n') {
            input[--length] = '\0';
            break;
        }

        if (feof(stdin)) {
            break;
        }

        if (capacity > SIZE_MAX / 2) {
            free(input);
            return EXIT_FAILURE;
        }

        size_t new_capacity = capacity * 2;

        if (new_capacity > (size_t)INT_MAX) {
            new_capacity = (size_t)INT_MAX;
        }

        if (new_capacity <= capacity) {
            free(input);
            return EXIT_FAILURE;
        }

        char *new_input = realloc(input, new_capacity);
        if (new_input == NULL) {
            free(input);
            return EXIT_FAILURE;
        }

        input = new_input;
        capacity = new_capacity;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    char *word = find_first_longest_even_word(input);
    free(input);

    if (word == NULL) {
        puts("No even-length word found.");
        return EXIT_SUCCESS;
    }

    puts(word);
    free(word);

    return EXIT_SUCCESS;
}
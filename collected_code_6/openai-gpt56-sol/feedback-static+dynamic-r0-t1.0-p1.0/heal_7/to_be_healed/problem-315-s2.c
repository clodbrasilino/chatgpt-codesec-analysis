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
            continue;
        }

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

    if (best_start == NULL || best_length > SIZE_MAX - 1) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  result_size is assigned 'best_length+1' here.
     */
    size_t result_size = best_length + 1;
    char *result = malloc(result_size);

    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'best_length>=result_size' is always false [knownConditionTrueFalse]
     *  Condition 'best_length>=result_size' is always false
     */
    if (best_length >= result_size) {
        free(result);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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

    input[0] = '\0';

    for (;;) {
        if (capacity - length < 2) {
            if (capacity > SIZE_MAX / 2) {
                free(input);
                return EXIT_FAILURE;
            }

            size_t new_capacity = capacity * 2;
            char *new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        size_t available = capacity - length;
        size_t bytes_read = fread(input + length, 1, available - 1, stdin);

        length += bytes_read;
        input[length] = '\0';

        /* Possible weaknesses found:
         *  Variable 'newline' can be declared as pointer to const [constVariablePointer]
         */
        char *newline = memchr(input, '\n', length);

        if (newline != NULL) {
            length = (size_t)(newline - input);
            input[length] = '\0';
            break;
        }

        if (bytes_read == 0) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }
    }

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
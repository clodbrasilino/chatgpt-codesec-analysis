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

        while (*current != '\0' && isspace((unsigned char)*current)) {
            ++current;
        }

        word_start = current;

        while (*current != '\0' && !isspace((unsigned char)*current)) {
            ++word_length;
            ++current;
        }

        if (word_length != 0 && word_length % 2 == 0 &&
            word_length > maximum_length) {
            result->start = word_start;
            result->length = word_length;
            maximum_length = word_length;
        }
    }

    return result->start != NULL;
}

static bool read_input(char **buffer)
{
    size_t capacity = 256;
    size_t length = 0;
    char *data;
    int character;

    if (buffer == NULL) {
        return false;
    }

    data = malloc(capacity);
    if (data == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (length + 1 >= capacity) {
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(data);
                return false;
            }

            capacity *= 2;
            resized = realloc(data, capacity);
            if (resized == NULL) {
                free(data);
                return false;
            }

            data = resized;
        }

        data[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(data);
        return false;
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
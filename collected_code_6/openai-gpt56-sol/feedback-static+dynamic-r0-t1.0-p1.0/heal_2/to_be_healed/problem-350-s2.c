#include <stdio.h>
#include <stdlib.h>

char *remove_character(const char *input, size_t input_length, char character)
{
    size_t output_length = 0;
    size_t i;
    char *output;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    for (i = 0; i < input_length; ++i) {
        if (input[i] != character) {
            ++output_length;
        }
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    output_length = 0;

    for (i = 0; i < input_length; ++i) {
        if (input[i] != character) {
            output[output_length++] = input[i];
        }
    }

    output[output_length] = '\0';
    return output;
}

static char *read_line(size_t *length)
{
    size_t capacity = 128;
    size_t used = 0;
    char *line;
    int ch;

    if (length == NULL) {
        return NULL;
    }

    line = malloc(capacity);
    if (line == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (used + 1 == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(line);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[used++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || used == 0)) {
        free(line);
        return NULL;
    }

    line[used] = '\0';
    *length = used;
    return line;
}

int main(void)
{
    char *input;
    char *character_line;
    char *result;
    size_t input_length;
    size_t character_length;

    input = read_line(&input_length);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    character_line = read_line(&character_length);
    if (character_line == NULL || character_length != 1) {
        free(character_line);
        free(input);
        return EXIT_FAILURE;
    }

    result = remove_character(input, input_length, character_line[0]);
    free(character_line);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
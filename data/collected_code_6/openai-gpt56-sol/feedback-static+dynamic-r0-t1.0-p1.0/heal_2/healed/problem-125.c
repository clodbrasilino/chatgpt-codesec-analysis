#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 1000000U

static int maximum_difference(const char *binary_string,
                              size_t length,
                              size_t *start,
                              size_t *end)
{
    int maximum = 0;
    int current = 0;
    size_t current_start = 0;

    if (binary_string == NULL || start == NULL || end == NULL) {
        return -1;
    }

    *start = 0;
    *end = 0;

    for (size_t i = 0; i < length; ++i) {
        int value;

        if (binary_string[i] == '0') {
            value = 1;
        } else if (binary_string[i] == '1') {
            value = -1;
        } else {
            return -1;
        }

        if (current < 0) {
            current = value;
            current_start = i;
        } else {
            current += value;
        }

        if (current > maximum) {
            maximum = current;
            *start = current_start;
            *end = i;
        }
    }

    return maximum;
}

static int discard_line(void)
{
    int character;

    do {
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return character;
}

int main(void)
{
    const size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    char *input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    if (fgets(input, (int)capacity, stdin) == NULL) {
        free(input);
        return EXIT_FAILURE;
    }

    size_t length = 0;

    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\r') {
        if (input[length + 1U] == '\n') {
            input[length + 1U] = '\0';
        } else if (input[length + 1U] == '\0') {
            int character = fgetc(stdin);

            if (character != '\n' && character != EOF) {
                if (character != '\r') {
                    discard_line();
                }
                free(input);
                return EXIT_FAILURE;
            }
        }

        input[length] = '\0';
    } else if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int character;

        if (length > MAX_INPUT_LENGTH) {
            discard_line();
            free(input);
            return EXIT_FAILURE;
        }

        character = fgetc(stdin);

        if (character == '\r') {
            character = fgetc(stdin);
            if (character != '\n' && character != EOF) {
                discard_line();
                free(input);
                return EXIT_FAILURE;
            }
        } else if (character != '\n' && character != EOF) {
            discard_line();
            free(input);
            return EXIT_FAILURE;
        }
    }

    if (length == 0U || length > MAX_INPUT_LENGTH) {
        free(input);
        return EXIT_FAILURE;
    }

    size_t start;
    size_t end;
    int result = maximum_difference(input, length, &start, &end);

    free(input);

    if (result < 0) {
        return EXIT_FAILURE;
    }

    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
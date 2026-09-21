#include <stdint.h>
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

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || required == 0) {
        return -1;
    }

    new_capacity = (*capacity == 0) ? 128 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity < required) {
        return -1;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_line(char **buffer, size_t *length)
{
    size_t capacity = 0;

    if (buffer == NULL || length == NULL) {
        return -1;
    }

    *buffer = NULL;
    *length = 0;

    for (;;) {
        int ch = getchar();

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || *length == 0) {
                free(*buffer);
                *buffer = NULL;
                *length = 0;
                return -1;
            }
            break;
        }

        if (*length == SIZE_MAX - 1) {
            free(*buffer);
            *buffer = NULL;
            *length = 0;
            return -1;
        }

        if (grow_buffer(buffer, &capacity, *length + 2) != 0) {
            free(*buffer);
            *buffer = NULL;
            *length = 0;
            return -1;
        }

        (*buffer)[*length] = (char)ch;
        ++*length;
    }

    if (grow_buffer(buffer, &capacity, *length + 1) != 0) {
        free(*buffer);
        *buffer = NULL;
        *length = 0;
        return -1;
    }

    (*buffer)[*length] = '\0';
    return 0;
}

static int read_character(char *character)
{
    char line[3];

    if (character == NULL) {
        return -1;
    }

    if (fgets(line, sizeof line, stdin) == NULL) {
        return -1;
    }

    if (line[0] == '\n' || line[0] == '\0') {
        return -1;
    }

    if (line[1] == '\n') {
        *character = line[0];
        return 0;
    }

    if (line[1] == '\0' && feof(stdin)) {
        *character = line[0];
        return 0;
    }

    for (;;) {
        char discard[128];

        if (fgets(discard, sizeof discard, stdin) == NULL) {
            break;
        }

        {
            size_t i;

            for (i = 0; discard[i] != '\0'; ++i) {
                if (discard[i] == '\n') {
                    return -1;
                }
            }
        }
    }

    return -1;
}

int main(void)
{
    char *input = NULL;
    char *result;
    char character;
    size_t length;

    if (read_line(&input, &length) != 0) {
        return EXIT_FAILURE;
    }

    if (read_character(&character) != 0) {
        free(input);
        return EXIT_FAILURE;
    }

    result = remove_character(input, length, character);
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
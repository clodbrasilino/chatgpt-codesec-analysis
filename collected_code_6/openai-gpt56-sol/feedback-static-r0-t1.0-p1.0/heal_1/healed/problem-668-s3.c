#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *collapse_character(const char *input, size_t input_size, char target)
{
    const char *terminator;
    size_t length;
    size_t read_index;
    size_t write_index;
    int previous_was_target;
    char *output;

    if (input == NULL || input_size == 0U) {
        return NULL;
    }

    terminator = memchr(input, '\0', input_size);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - input);
    output = malloc(length + 1U);
    if (output == NULL) {
        return NULL;
    }

    write_index = 0U;
    previous_was_target = 0;

    for (read_index = 0U; read_index < length; ++read_index) {
        if (input[read_index] == target) {
            if (previous_was_target != 0) {
                continue;
            }
            previous_was_target = 1;
        } else {
            previous_was_target = 0;
        }

        output[write_index++] = input[read_index];
    }

    output[write_index] = '\0';
    return output;
}

int main(void)
{
    const char input[] = "This   string    contains  repeated spaces.";
    char *result = collapse_character(input, sizeof(input), ' ');

    if (result == NULL) {
        fputs("Failed to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

char *collapse_character(const char *input, size_t input_size, char target)
{
    size_t read_index = 0U;
    size_t write_index = 0U;
    int previous_was_target = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    while (read_index < input_size && input[read_index] != '\0') {
        ++read_index;
    }

    if (read_index == input_size) {
        return NULL;
    }

    output = malloc(read_index + 1U);
    if (output == NULL) {
        return NULL;
    }

    input_size = read_index;

    for (read_index = 0U; read_index < input_size; ++read_index) {
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
    char *result = collapse_character(input, sizeof input, ' ');

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
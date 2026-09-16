#include <stdio.h>
#include <stdlib.h>

char *collapse_character(const char *input, char target)
{
    size_t read_index = 0;
    size_t write_index = 0;
    char *result;
    int previous_was_target = 0;

    if (input == NULL) {
        return NULL;
    }

    while (input[read_index] != '\0') {
        read_index++;
    }

    result = malloc(read_index + 1);
    if (result == NULL) {
        return NULL;
    }

    read_index = 0;

    while (input[read_index] != '\0') {
        if (input[read_index] != target || !previous_was_target) {
            result[write_index++] = input[read_index];
        }

        previous_was_target = input[read_index] == target;
        read_index++;
    }

    result[write_index] = '\0';
    return result;
}

int main(void)
{
    const char input[] = "This    is  a   sample.";
    char *result = collapse_character(input, ' ');

    if (result == NULL) {
        fputs("Failed to process the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_odd_indexed_characters(const char *input)
{
    size_t input_length;
    size_t output_length;
    char *output;
    size_t source_index;
    size_t destination_index;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);
    output_length = (input_length + 1U) / 2U;

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    destination_index = 0U;
    for (source_index = 0U; source_index < input_length; source_index += 2U) {
        output[destination_index++] = input[source_index];
    }

    output[destination_index] = '\0';
    return output;
}

int main(void)
{
    char input[1024];
    char *result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    result = remove_odd_indexed_characters(input);
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_even_characters(const char *input)
{
    size_t length;
    size_t output_length;
    size_t source_index;
    size_t destination_index;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);
    output_length = length / 2U;

    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    destination_index = 0U;
    for (source_index = 1U; source_index < length; source_index += 2U) {
        output[destination_index++] = input[source_index];
    }
    output[destination_index] = '\0';

    return output;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    char *result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    input[strcspn(input, "\n")] = '\0';

    result = remove_even_characters(input);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
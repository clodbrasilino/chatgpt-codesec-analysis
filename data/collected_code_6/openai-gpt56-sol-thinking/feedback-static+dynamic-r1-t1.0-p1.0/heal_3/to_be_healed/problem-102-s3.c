#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int get_string_length(const char *input, size_t *length)
{
    size_t count = 0;

    if (input == NULL || length == NULL) {
        return 0;
    }

    while (input[count] != '\0') {
        if (count == SIZE_MAX - 1) {
            return 0;
        }
        ++count;
    }

    *length = count;
    return 1;
}

static char *snake_to_camel(const char *input, size_t input_length)
{
    size_t source_index;
    size_t destination_index = 0;
    int capitalize_next = 1;
    char *result;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (source_index = 0; source_index < input_length; ++source_index) {
        unsigned char character = (unsigned char)input[source_index];

        if (character == '\0') {
            free(result);
            return NULL;
        }

        if (character == (unsigned char)'_') {
            capitalize_next = 1;
            continue;
        }

        if (capitalize_next) {
            character = (unsigned char)toupper((int)character);
            capitalize_next = 0;
        }

        result[destination_index++] = (char)character;
    }

    result[destination_index] = '\0';
    return result;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *program_name;
    size_t input_length;
    char *camel_case;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (!get_string_length(argv[1], &input_length)) {
        fputs("Invalid input string.\n", stderr);
        return EXIT_FAILURE;
    }

    camel_case = snake_to_camel(argv[1], input_length);
    if (camel_case == NULL) {
        fputs("Failed to convert string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(camel_case) == EOF) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}
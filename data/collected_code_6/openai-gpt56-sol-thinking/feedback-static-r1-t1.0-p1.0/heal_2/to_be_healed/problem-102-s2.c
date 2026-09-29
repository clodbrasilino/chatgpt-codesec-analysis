#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *snake_to_camel(const char *input, size_t input_length)
{
    char *output;
    size_t read_index;
    size_t write_index = 0;
    int capitalize_next = 0;

    if (input == NULL || input_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(input_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (read_index = 0; read_index < input_length; ++read_index) {
        unsigned char current = (unsigned char)input[read_index];

        if (current == (unsigned char)'_') {
            capitalize_next = 1;
        } else if (capitalize_next) {
            output[write_index++] = (char)toupper(current);
            capitalize_next = 0;
        } else {
            output[write_index++] = (char)current;
        }
    }

    output[write_index] = '\0';
    return output;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    char *converted;
    size_t input_length;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(argv[1]);
    converted = snake_to_camel(argv[1], input_length);
    if (converted == NULL) {
        fputs("Failed to convert the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (puts(converted) == EOF) {
        fputs("Failed to write the converted string.\n", stderr);
        status = EXIT_FAILURE;
    }

    free(converted);
    return status;
}
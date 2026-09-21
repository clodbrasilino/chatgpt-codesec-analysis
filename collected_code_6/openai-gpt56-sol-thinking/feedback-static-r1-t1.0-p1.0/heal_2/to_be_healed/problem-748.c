#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int requires_space(unsigned char previous, unsigned char current)
{
    return (islower(previous) || isdigit(previous)) && isupper(current);
}

char *insert_spaces_before_capitals(const char *input, size_t input_length)
{
    size_t spaces = 0;
    size_t capacity;
    size_t output_position = 0;
    char *output;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    for (size_t i = 1; i < input_length; ++i) {
        if (requires_space((unsigned char)input[i - 1],
                           (unsigned char)input[i])) {
            ++spaces;
        }
    }

    if (input_length == SIZE_MAX ||
        spaces > SIZE_MAX - input_length - 1U) {
        errno = EOVERFLOW;
        return NULL;
    }

    capacity = input_length + spaces + 1U;
    output = malloc(capacity);
    if (output == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (size_t i = 0; i < input_length; ++i) {
        if (i > 0 &&
            requires_space((unsigned char)input[i - 1],
                           (unsigned char)input[i])) {
            output[output_position++] = ' ';
        }

        output[output_position++] = input[i];
    }

    output[output_position] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    const char *input;
    char *result;
    size_t input_length;

    program_name = (argc > 0 && argv != NULL && argv[0] != NULL)
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    result = insert_spaces_before_capitals(input, input_length);
    if (result == NULL) {
        perror("Unable to transform string");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
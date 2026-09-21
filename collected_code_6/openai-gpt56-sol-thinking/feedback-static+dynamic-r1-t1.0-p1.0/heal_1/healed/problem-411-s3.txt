#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_ascii_alphanumeric(unsigned char character)
{
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z') ||
           (character >= '0' && character <= '9');
}

static unsigned char to_ascii_upper(unsigned char character)
{
    if (character >= 'a' && character <= 'z') {
        return (unsigned char)(character - ('a' - 'A'));
    }

    return character;
}

char *snake_case_to_camel_case(const char *input, size_t input_length)
{
    char *result;
    size_t source_index = 0;
    size_t destination_index = 0;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (input_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    while (source_index < input_length) {
        unsigned char current = (unsigned char)input[source_index];

        if (current == '_' &&
            input_length - source_index >= 2 &&
            is_ascii_alphanumeric(
                (unsigned char)input[source_index + 1])) {
            result[destination_index++] = (char)to_ascii_upper(
                (unsigned char)input[source_index + 1]);
            source_index += 2;
        } else {
            result[destination_index++] = (char)current;
            ++source_index;
        }
    }

    result[destination_index] = '\0';
    return result;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    const char *input;
    char *camel_case;
    size_t input_length = 0;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];

    while (input[input_length] != '\0') {
        if (input_length == SIZE_MAX - 1) {
            errno = EOVERFLOW;
            perror("snake_case_to_camel_case");
            return EXIT_FAILURE;
        }

        ++input_length;
    }

    camel_case = snake_case_to_camel_case(input, input_length);
    if (camel_case == NULL) {
        perror("snake_case_to_camel_case");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", camel_case) < 0) {
        free(camel_case);
        return EXIT_FAILURE;
    }

    free(camel_case);
    return EXIT_SUCCESS;
}
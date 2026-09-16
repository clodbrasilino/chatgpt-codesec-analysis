#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_ascii_alphanumeric(unsigned char character)
{
    return (character >= 'A' && character <= 'Z') ||
           (character >= 'a' && character <= 'z') ||
           (character >= '0' && character <= '9');
}

char *snake_case_to_camel_case(const char *input)
{
    size_t input_length;
    size_t source_index;
    size_t destination_index;
    char *result;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    source_index = 0;
    destination_index = 0;

    while (source_index < input_length) {
        unsigned char character = (unsigned char)input[source_index];

        if (character == '_' &&
            source_index + 1 < input_length &&
            is_ascii_alphanumeric((unsigned char)input[source_index + 1])) {
            result[destination_index++] =
                (char)toupper((unsigned char)input[source_index + 1]);
            source_index += 2;
        } else {
            result[destination_index++] = (char)character;
            ++source_index;
        }
    }

    result[destination_index] = '\0';
    return result;
}

int main(int argc, char *argv[const])
{
    const char *program_name;
    char *camel_case;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <snake_case_string>\n", program_name);
        return EXIT_FAILURE;
    }

    camel_case = snake_case_to_camel_case(argv[1]);
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
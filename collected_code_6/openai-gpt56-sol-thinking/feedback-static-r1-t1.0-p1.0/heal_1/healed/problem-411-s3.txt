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
    const unsigned char *source;
    char *result;
    char *destination;
    size_t length;

    if (input == NULL) {
        errno = EINVAL;
        return NULL;
    }

    length = strlen(input);
    if (length == SIZE_MAX) {
        errno = EOVERFLOW;
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    source = (const unsigned char *)input;
    destination = result;

    while (*source != '\0') {
        if (*source == '_' && is_ascii_alphanumeric(source[1])) {
            *destination++ = (char)toupper(source[1]);
            source += 2;
        } else {
            *destination++ = (char)*source++;
        }
    }

    *destination = '\0';
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
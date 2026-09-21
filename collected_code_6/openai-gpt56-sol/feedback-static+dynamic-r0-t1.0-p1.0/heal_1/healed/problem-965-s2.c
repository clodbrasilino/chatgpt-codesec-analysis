#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *camel_to_snake(const char *input)
{
    const unsigned char *p;
    size_t output_length = 0;
    size_t j = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    for (p = (const unsigned char *)input; *p != '\0'; ++p) {
        int insert_underscore = 0;

        if (isupper(*p)) {
            int previous_is_lower_or_digit =
                p != (const unsigned char *)input &&
                (islower(p[-1]) || isdigit(p[-1]));
            int next_is_lower = p[1] != '\0' && islower(p[1]);

            insert_underscore =
                output_length > 0 &&
                (previous_is_lower_or_digit || next_is_lower);
        }

        if (output_length == SIZE_MAX) {
            return NULL;
        }
        ++output_length;

        if (insert_underscore) {
            if (output_length == SIZE_MAX) {
                return NULL;
            }
            ++output_length;
        }
    }

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1);
    if (output == NULL) {
        return NULL;
    }

    for (p = (const unsigned char *)input; *p != '\0'; ++p) {
        if (isupper(*p)) {
            int previous_is_lower_or_digit =
                p != (const unsigned char *)input &&
                (islower(p[-1]) || isdigit(p[-1]));
            int next_is_lower = p[1] != '\0' && islower(p[1]);

            if (j > 0 && (previous_is_lower_or_digit || next_is_lower)) {
                output[j++] = '_';
            }

            output[j++] = (char)tolower(*p);
        } else {
            output[j++] = (char)*p;
        }
    }

    output[j] = '\0';
    return output;
}

int main(int argc, char *argv[])
{
    const char *input;
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "camel_to_snake");
        return EXIT_FAILURE;
    }

    input = argv[1];
    result = camel_to_snake(input);
    if (result == NULL) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
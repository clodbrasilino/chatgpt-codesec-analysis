#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *camel_to_snake(const char *input)
{
    size_t input_length;
    size_t output_index = 0U;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    input_length = strlen(input);

    if (input_length > (SIZE_MAX - 1U) / 2U) {
        return NULL;
    }

    output = malloc(input_length * 2U + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (size_t input_index = 0U;
         input_index < input_length;
         ++input_index) {
        unsigned char current = (unsigned char)input[input_index];

        if (isupper(current)) {
            int follows_lower_or_digit =
                input_index > 0U &&
                (islower((unsigned char)input[input_index - 1U]) ||
                 isdigit((unsigned char)input[input_index - 1U]));

            int starts_word_before_lower =
                input_index > 0U &&
                input_index + 1U < input_length &&
                islower((unsigned char)input[input_index + 1U]);

            if ((follows_lower_or_digit || starts_word_before_lower) &&
                output_index > 0U &&
                output[output_index - 1U] != '_') {
                output[output_index++] = '_';
            }

            output[output_index++] = (char)tolower(current);
        } else {
            output[output_index++] = (char)current;
        }
    }

    output[output_index] = '\0';
    return output;
}

int main(int argc, char *argv[const])
{
    char *snake_case;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "camel_to_snake";

        fprintf(stderr, "Usage: %s <camelCaseString>\n", program_name);
        return EXIT_FAILURE;
    }

    snake_case = camel_to_snake(argv[1]);
    if (snake_case == NULL) {
        fprintf(stderr, "Failed to convert the input string.\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", snake_case) < 0) {
        free(snake_case);
        return EXIT_FAILURE;
    }

    free(snake_case);
    return EXIT_SUCCESS;
}
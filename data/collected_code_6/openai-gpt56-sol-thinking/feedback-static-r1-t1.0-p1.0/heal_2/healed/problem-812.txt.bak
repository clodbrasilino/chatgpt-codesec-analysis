#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

int abbreviate_road(const char *input, char **output)
{
    size_t input_length;
    size_t input_index = 0;
    size_t output_index = 0;
    char *result;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;
    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        return -1;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    while (input_index < input_length) {
        size_t remaining = input_length - input_index;
        int left_boundary =
            input_index == 0 ||
            !is_word_character((unsigned char)input[input_index - 1]);
        int right_boundary =
            remaining >= 4 &&
            (input_index + 4 == input_length ||
             !is_word_character((unsigned char)input[input_index + 4]));

        if (remaining >= 4 &&
            left_boundary &&
            right_boundary &&
            memcmp(input + input_index, "road", 4) == 0) {
            result[output_index++] = 'r';
            result[output_index++] = 'd';
            result[output_index++] = '.';
            input_index += 4;
        } else {
            result[output_index++] = input[input_index++];
        }
    }

    result[output_index] = '\0';
    *output = result;

    return 0;
}

int main(int argc, const char *const argv[])
{
    char *abbreviated = NULL;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"text\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (abbreviate_road(argv[1], &abbreviated) != 0) {
        fputs("Failed to abbreviate the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", abbreviated) < 0) {
        free(abbreviated);
        return EXIT_FAILURE;
    }

    free(abbreviated);
    return EXIT_SUCCESS;
}
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH ((size_t)16 * 1024 * 1024)

static int is_word_character(unsigned char character)
{
    return isalnum(character) != 0 || character == '_';
}

static int get_bounded_string_length(const char *string, size_t limit,
                                     size_t *length)
{
    size_t index;

    if (string == NULL || length == NULL) {
        return -1;
    }

    for (index = 0; index < limit; ++index) {
        if (string[index] == '\0') {
            *length = index;
            return 0;
        }
    }

    return -1;
}

static int abbreviate_road(const char *input, size_t input_length, char **output)
{
    size_t input_index = 0;
    size_t output_index = 0;
    char *result;

    if (input == NULL || output == NULL || input_length == SIZE_MAX) {
        return -1;
    }

    *output = NULL;

    result = malloc(input_length + 1);
    if (result == NULL) {
        return -1;
    }

    while (input_index < input_length) {
        size_t remaining = input_length - input_index;
        int left_boundary;
        int right_boundary;

        left_boundary =
            input_index == 0 ||
            !is_word_character((unsigned char)input[input_index - 1]);

        right_boundary =
            remaining >= 4 &&
            (remaining == 4 ||
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    size_t input_length;
    char *abbreviated = NULL;

    if (argc != 2) {
        fputs("Usage: abbreviate_road \"text\"\n", stderr);
        return EXIT_FAILURE;
    }

    if (get_bounded_string_length(argv[1], MAX_INPUT_LENGTH,
                                  &input_length) != 0) {
        fputs("Input is too long or is not properly terminated.\n", stderr);
        return EXIT_FAILURE;
    }

    if (abbreviate_road(argv[1], input_length, &abbreviated) != 0) {
        fputs("Failed to abbreviate the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fputs(abbreviated, stdout) == EOF ||
        fputc('\n', stdout) == EOF) {
        free(abbreviated);
        return EXIT_FAILURE;
    }

    free(abbreviated);
    return EXIT_SUCCESS;
}
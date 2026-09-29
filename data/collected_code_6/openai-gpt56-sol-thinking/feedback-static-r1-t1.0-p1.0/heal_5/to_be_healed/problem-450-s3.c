#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string_view {
    const char *data;
    size_t length;
};

static void free_string_list(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int extract_strings_by_length(
    const struct string_view *input,
    size_t input_count,
    size_t requested_length,
    char ***output,
    size_t *output_count)
{
    char **result;
    size_t match_count = 0;
    size_t result_index = 0;
    size_t i;

    if (output == NULL || output_count == NULL) {
        return EINVAL;
    }

    *output = NULL;
    *output_count = 0;

    if (input_count != 0 && input == NULL) {
        return EINVAL;
    }

    for (i = 0; i < input_count; ++i) {
        if (input[i].data == NULL) {
            return EINVAL;
        }

        if (input[i].length == requested_length) {
            ++match_count;
        }
    }

    if (match_count == 0) {
        return 0;
    }

    if (requested_length == SIZE_MAX ||
        match_count > SIZE_MAX / sizeof(*result)) {
        return ENOMEM;
    }

    result = calloc(match_count, sizeof(*result));
    if (result == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < input_count; ++i) {
        size_t character_index;

        if (input[i].length != requested_length) {
            continue;
        }

        result[result_index] = malloc(requested_length + 1);
        if (result[result_index] == NULL) {
            free_string_list(result, result_index);
            return ENOMEM;
        }

        for (character_index = 0;
             character_index < requested_length;
             ++character_index) {
            result[result_index][character_index] =
                input[i].data[character_index];
        }

        result[result_index][requested_length] = '\0';
        ++result_index;
    }

    *output = result;
    *output_count = result_index;
    return 0;
}

static int parse_size(const char *text, size_t *value)
{
    const unsigned char *current;
    size_t parsed = 0;

    if (text == NULL || value == NULL) {
        return EINVAL;
    }

    current = (const unsigned char *)text;

    if (*current == '+') {
        ++current;
    } else if (*current == '-') {
        return EINVAL;
    }

    if (*current == '\0') {
        return EINVAL;
    }

    while (*current != '\0') {
        size_t digit;

        if (*current < (unsigned char)'0' ||
            *current > (unsigned char)'9') {
            return EINVAL;
        }

        digit = (size_t)(*current - (unsigned char)'0');

        if (parsed > (SIZE_MAX - digit) / 10) {
            return ERANGE;
        }

        parsed = parsed * 10 + digit;
        ++current;
    }

    *value = parsed;
    return 0;
}

int main(int argc, char **const argv)
{
    struct string_view *input = NULL;
    char **matches = NULL;
    const char *program_name = "program";
    size_t input_count;
    size_t match_count = 0;
    size_t requested_length;
    size_t i;
    int status;
    int exit_status = EXIT_SUCCESS;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc < 2 || argv == NULL) {
        fprintf(stderr, "Usage: %s LENGTH [STRING ...]\n", program_name);
        return EXIT_FAILURE;
    }

    status = parse_size(argv[1], &requested_length);
    if (status != 0) {
        fprintf(stderr, "Invalid length: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    input_count = (size_t)(argc - 2);

    if (input_count != 0) {
        if (input_count > SIZE_MAX / sizeof(*input)) {
            fprintf(stderr, "Input list is too large\n");
            return EXIT_FAILURE;
        }

        input = malloc(input_count * sizeof(*input));
        if (input == NULL) {
            fprintf(stderr, "Unable to allocate input list\n");
            return EXIT_FAILURE;
        }

        for (i = 0; i < input_count; ++i) {
            if (argv[i + 2] == NULL) {
                fprintf(stderr, "Invalid input string\n");
                free(input);
                return EXIT_FAILURE;
            }

            input[i].data = argv[i + 2];
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            input[i].length = strlen(argv[i + 2]);
        }
    }

    status = extract_strings_by_length(
        input,
        input_count,
        requested_length,
        &matches,
        &match_count
    );

    free(input);

    if (status != 0) {
        fprintf(stderr, "Extraction failed: %s\n", strerror(status));
        return EXIT_FAILURE;
    }

    for (i = 0; i < match_count; ++i) {
        if (puts(matches[i]) == EOF) {
            exit_status = EXIT_FAILURE;
            break;
        }
    }

    free_string_list(matches, match_count);
    return exit_status;
}
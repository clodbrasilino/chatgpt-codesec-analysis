#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} string_ref;

static size_t get_string_length(const char *text)
{
    size_t length = 0;

    while (text[length] != '\0') {
        ++length;
    }

    return length;
}

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

static int copy_string_ref(const string_ref *source, char **destination)
{
    char *copy;
    size_t i;

    if (source == NULL || destination == NULL || source->data == NULL) {
        return EINVAL;
    }

    *destination = NULL;

    if (source->length == SIZE_MAX) {
        return ENOMEM;
    }

    copy = malloc(source->length + 1);
    if (copy == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < source->length; ++i) {
        copy[i] = source->data[i];
    }

    copy[source->length] = '\0';
    *destination = copy;
    return 0;
}

static int extract_strings_by_length(
    const string_ref *input,
    size_t input_count,
    size_t requested_length,
    char ***output,
    size_t *output_count)
{
    char **result;
    size_t match_count = 0;
    size_t result_index = 0;
    size_t i;
    int status;

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

    if (match_count > SIZE_MAX / sizeof(*result)) {
        return ENOMEM;
    }

    result = calloc(match_count, sizeof(*result));
    if (result == NULL) {
        return ENOMEM;
    }

    for (i = 0; i < input_count; ++i) {
        if (input[i].length != requested_length) {
            continue;
        }

        status = copy_string_ref(&input[i], &result[result_index]);
        if (status != 0) {
            free_string_list(result, result_index);
            return status;
        }

        ++result_index;
    }

    *output = result;
    *output_count = result_index;
    return 0;
}

static int parse_size(const char *text, size_t *value)
{
    size_t parsed = 0;
    size_t i;

    if (text == NULL || value == NULL || text[0] == '\0') {
        return EINVAL;
    }

    for (i = 0; text[i] != '\0'; ++i) {
        size_t digit;

        if (text[i] < '0' || text[i] > '9') {
            return EINVAL;
        }

        digit = (size_t)(text[i] - '0');

        if (parsed > (SIZE_MAX - digit) / 10) {
            return ERANGE;
        }

        parsed = parsed * 10 + digit;
    }

    *value = parsed;
    return 0;
}

int main(int argc, char *argv[])
{
    string_ref *input = NULL;
    char **matches = NULL;
    size_t input_count;
    size_t match_count = 0;
    size_t requested_length;
    size_t i;
    int status;
    int exit_status = EXIT_SUCCESS;
    const char *program_name;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
        ? argv[0]
        : "program";

    if (argc < 2 || argv == NULL || argv[1] == NULL) {
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
            const char *argument = argv[i + 2];

            if (argument == NULL) {
                free(input);
                fprintf(stderr, "Invalid input string\n");
                return EXIT_FAILURE;
            }

            input[i].data = argument;
            input[i].length = get_string_length(argument);
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
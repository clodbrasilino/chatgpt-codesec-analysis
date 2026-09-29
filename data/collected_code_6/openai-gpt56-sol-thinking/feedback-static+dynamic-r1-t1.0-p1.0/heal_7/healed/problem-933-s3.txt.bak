#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CAMEL_OK = 0,
    CAMEL_INVALID_ARGUMENT,
    CAMEL_OUT_OF_MEMORY,
    CAMEL_REGEX_ERROR,
    CAMEL_OVERFLOW
} CamelStatus;

static int valid_match(const regmatch_t matches[3], size_t remaining)
{
    size_t full_start;
    size_t full_end;
    size_t first_start;
    size_t first_end;
    size_t second_start;
    size_t second_end;

    if (matches[0].rm_so < 0 || matches[0].rm_eo < 0 ||
        matches[1].rm_so < 0 || matches[1].rm_eo < 0 ||
        matches[2].rm_so < 0 || matches[2].rm_eo < 0) {
        return 0;
    }

    full_start = (size_t)matches[0].rm_so;
    full_end = (size_t)matches[0].rm_eo;
    first_start = (size_t)matches[1].rm_so;
    first_end = (size_t)matches[1].rm_eo;
    second_start = (size_t)matches[2].rm_so;
    second_end = (size_t)matches[2].rm_eo;

    return full_start == first_start &&
           first_end == second_start &&
           second_end == full_end &&
           full_start < full_end &&
           full_end <= remaining;
}

static CamelStatus replace_boundaries(
    const char *input,
    const regex_t *pattern,
    char **output)
{
    regmatch_t matches[3];
    size_t input_length;
    size_t position;
    size_t match_count;
    size_t output_length;
    size_t destination;
    char *result;
    int regex_result;

    if (output == NULL) {
        return CAMEL_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input == NULL || pattern == NULL) {
        return CAMEL_INVALID_ARGUMENT;
    }

    input_length = strlen(input);
    position = 0;
    match_count = 0;

    while (position < input_length) {
        regex_result = regexec(pattern, input + position, 3, matches, 0);

        if (regex_result == REG_NOMATCH) {
            break;
        }

        if (regex_result != 0 ||
            !valid_match(matches, input_length - position)) {
            return CAMEL_REGEX_ERROR;
        }

        if (match_count == SIZE_MAX) {
            return CAMEL_OVERFLOW;
        }

        ++match_count;
        position += (size_t)matches[0].rm_eo;
    }

    if (input_length == SIZE_MAX ||
        match_count > SIZE_MAX - input_length - 1) {
        return CAMEL_OVERFLOW;
    }

    output_length = input_length + match_count;
    result = malloc(output_length + 1);

    if (result == NULL) {
        return CAMEL_OUT_OF_MEMORY;
    }

    position = 0;
    destination = 0;

    while (position < input_length) {
        size_t boundary;
        size_t match_end;
        size_t prefix_length;
        size_t suffix_length;

        regex_result = regexec(pattern, input + position, 3, matches, 0);

        if (regex_result == REG_NOMATCH) {
            break;
        }

        if (regex_result != 0 ||
            !valid_match(matches, input_length - position)) {
            free(result);
            return CAMEL_REGEX_ERROR;
        }

        boundary = (size_t)matches[1].rm_eo;
        match_end = (size_t)matches[0].rm_eo;
        prefix_length = boundary;
        suffix_length = match_end - boundary;

        memcpy(result + destination, input + position, prefix_length);
        destination += prefix_length;

        result[destination++] = '_';

        memcpy(
            result + destination,
            input + position + boundary,
            suffix_length
        );

        destination += suffix_length;
        position += match_end;
    }

    memcpy(
        result + destination,
        input + position,
        input_length - position
    );

    destination += input_length - position;

    if (destination != output_length) {
        free(result);
        return CAMEL_REGEX_ERROR;
    }

    result[destination] = '\0';
    *output = result;

    return CAMEL_OK;
}

CamelStatus camel_to_snake(const char *input, char **output)
{
    static const char acronym_expression[] = "([A-Z]+)([A-Z][a-z])";
    static const char capital_expression[] = "([a-z0-9])([A-Z])";
    regex_t pattern;
    char *intermediate;
    char *result;
    CamelStatus status;
    size_t index;

    if (output == NULL) {
        return CAMEL_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input == NULL) {
        return CAMEL_INVALID_ARGUMENT;
    }

    if (regcomp(&pattern, acronym_expression, REG_EXTENDED) != 0) {
        return CAMEL_REGEX_ERROR;
    }

    status = replace_boundaries(input, &pattern, &intermediate);
    regfree(&pattern);

    if (status != CAMEL_OK) {
        return status;
    }

    if (regcomp(&pattern, capital_expression, REG_EXTENDED) != 0) {
        free(intermediate);
        return CAMEL_REGEX_ERROR;
    }

    status = replace_boundaries(intermediate, &pattern, &result);
    regfree(&pattern);
    free(intermediate);

    if (status != CAMEL_OK) {
        return status;
    }

    for (index = 0; result[index] != '\0'; ++index) {
        if (result[index] >= 'A' && result[index] <= 'Z') {
            result[index] = (char)(result[index] - 'A' + 'a');
        }
    }

    *output = result;
    return CAMEL_OK;
}

static const char *camel_status_message(CamelStatus status)
{
    switch (status) {
        case CAMEL_OK:
            return "success";
        case CAMEL_INVALID_ARGUMENT:
            return "invalid argument";
        case CAMEL_OUT_OF_MEMORY:
            return "out of memory";
        case CAMEL_REGEX_ERROR:
            return "regular expression error";
        case CAMEL_OVERFLOW:
            return "size overflow";
        default:
            return "unknown error";
    }
}

int main(int argc, char * const argv[])
{
    char *snake_case;
    CamelStatus status;
    int print_result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = camel_to_snake(argv[1], &snake_case);

    if (status != CAMEL_OK) {
        fprintf(
            stderr,
            "Conversion failed: %s\n",
            camel_status_message(status)
        );
        return EXIT_FAILURE;
    }

    print_result = printf("%s\n", snake_case);
    free(snake_case);

    return print_result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} StringArray;

static void free_string_array(StringArray *array)
{
    if (array == NULL) {
        return;
    }

    for (size_t i = 0; i < array->count; ++i) {
        free(array->items[i]);
    }

    free(array->items);
    array->items = NULL;
    array->count = 0;
    array->capacity = 0;
}

static int append_token(StringArray *array, const char *start, size_t length)
{
    if (array == NULL || start == NULL || length == SIZE_MAX) {
        return -1;
    }

    char *token = malloc(length + 1);
    if (token == NULL) {
        return -1;
    }

    if (length > 0) {
        memmove(token, start, length);
    }
    token[length] = '\0';

    if (array->count == array->capacity) {
        size_t new_capacity = 8;

        if (array->capacity != 0) {
            if (array->capacity > SIZE_MAX / 2) {
                free(token);
                return -1;
            }
            new_capacity = array->capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*array->items)) {
            free(token);
            return -1;
        }

        char **new_items = realloc(
            array->items,
            new_capacity * sizeof(*array->items)
        );

        if (new_items == NULL) {
            free(token);
            return -1;
        }

        array->items = new_items;
        array->capacity = new_capacity;
    }

    array->items[array->count++] = token;
    return 0;
}

static int split_regex_n(const char *input,
                         size_t input_length,
                         const char *delimiter_pattern,
                         StringArray *result)
{
    if (input == NULL || delimiter_pattern == NULL || result == NULL) {
        return -1;
    }

    result->items = NULL;
    result->count = 0;
    result->capacity = 0;

    if (input_length == SIZE_MAX ||
        memchr(input, '\0', input_length) != NULL) {
        return -1;
    }

    char *terminated_input = malloc(input_length + 1);
    if (terminated_input == NULL) {
        return -1;
    }

    if (input_length > 0) {
        memmove(terminated_input, input, input_length);
    }
    terminated_input[input_length] = '\0';

    regex_t regex;
    if (regcomp(&regex, delimiter_pattern, REG_EXTENDED) != 0) {
        free(terminated_input);
        return -1;
    }

    size_t offset = 0;
    int return_value = 0;

    while (offset < input_length) {
        regmatch_t match;
        int status = regexec(
            &regex,
            terminated_input + offset,
            1,
            &match,
            0
        );

        if (status == REG_NOMATCH) {
            if (append_token(
                    result,
                    terminated_input + offset,
                    input_length - offset) != 0) {
                return_value = -1;
            }
            break;
        }

        if (status != 0 ||
            match.rm_so < 0 ||
            match.rm_eo < 0 ||
            match.rm_eo <= match.rm_so) {
            return_value = -1;
            break;
        }

        uintmax_t raw_start = (uintmax_t)match.rm_so;
        uintmax_t raw_end = (uintmax_t)match.rm_eo;
        size_t remaining = input_length - offset;

        if (raw_start > (uintmax_t)SIZE_MAX ||
            raw_end > (uintmax_t)SIZE_MAX ||
            raw_start > (uintmax_t)remaining ||
            raw_end > (uintmax_t)remaining) {
            return_value = -1;
            break;
        }

        size_t match_start = (size_t)raw_start;
        size_t match_end = (size_t)raw_end;

        if (match_start > 0 &&
            append_token(
                result,
                terminated_input + offset,
                match_start) != 0) {
            return_value = -1;
            break;
        }

        offset += match_end;
    }

    regfree(&regex);
    free(terminated_input);

    if (return_value != 0) {
        free_string_array(result);
    }

    return return_value;
}

int main(void)
{
    static const char input[] = "one,two;three four\tfive";
    static const char delimiters[] = "[,;[:space:]]+";
    StringArray tokens = {NULL, 0, 0};

    if (split_regex_n(
            input,
            sizeof(input) - 1,
            delimiters,
            &tokens) != 0) {
        fputs("Failed to split string\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tokens.count; ++i) {
        puts(tokens.items[i]);
    }

    free_string_array(&tokens);
    return EXIT_SUCCESS;
}
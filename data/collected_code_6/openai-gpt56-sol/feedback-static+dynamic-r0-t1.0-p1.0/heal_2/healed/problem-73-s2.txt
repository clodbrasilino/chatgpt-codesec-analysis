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

    for (size_t i = 0; i < length; ++i) {
        token[i] = start[i];
    }
    token[length] = '\0';

    if (array->count == array->capacity) {
        size_t new_capacity;

        if (array->capacity == 0) {
            new_capacity = 8;
        } else {
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

static int split_regex_n(const char *input, size_t input_length,
                         const char *delimiter_pattern, StringArray *result)
{
    if (input == NULL || delimiter_pattern == NULL || result == NULL) {
        return -1;
    }

    result->items = NULL;
    result->count = 0;
    result->capacity = 0;

    regex_t regex;
    if (regcomp(&regex, delimiter_pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    char *buffer = malloc(input_length + 1);
    if (buffer == NULL) {
        regfree(&regex);
        return -1;
    }

    for (size_t i = 0; i < input_length; ++i) {
        buffer[i] = input[i];
    }
    buffer[input_length] = '\0';

    size_t offset = 0;

    while (offset < input_length) {
        regmatch_t match;
        int status = regexec(&regex, buffer + offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (append_token(result, buffer + offset,
                             input_length - offset) != 0) {
                free(buffer);
                regfree(&regex);
                free_string_array(result);
                return -1;
            }
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo < 0) {
            free(buffer);
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        uintmax_t raw_start = (uintmax_t)match.rm_so;
        uintmax_t raw_end = (uintmax_t)match.rm_eo;
        size_t remaining = input_length - offset;

        if (raw_start > SIZE_MAX || raw_end > SIZE_MAX) {
            free(buffer);
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        size_t match_start = (size_t)raw_start;
        size_t match_end = (size_t)raw_end;

        if (match_start > match_end || match_end > remaining ||
            match_start == match_end) {
            free(buffer);
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        if (match_start != 0 &&
            append_token(result, buffer + offset, match_start) != 0) {
            free(buffer);
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        offset += match_end;
    }

    free(buffer);
    regfree(&regex);
    return 0;
}

int main(void)
{
    static const char input[] = "one,two;three four\tfive";
    static const char delimiters[] = "[,;[:space:]]+";
    StringArray tokens = {NULL, 0, 0};

    if (split_regex_n(input, sizeof(input) - 1, delimiters, &tokens) != 0) {
        fputs("Failed to split string\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tokens.count; ++i) {
        puts(tokens.items[i]);
    }

    free_string_array(&tokens);
    return EXIT_SUCCESS;
}
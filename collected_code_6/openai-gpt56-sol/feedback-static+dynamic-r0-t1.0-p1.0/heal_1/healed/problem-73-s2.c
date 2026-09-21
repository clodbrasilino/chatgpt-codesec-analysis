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
        memcpy(token, start, length);
    }
    token[length] = '\0';

    if (array->count == array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 8 : array->capacity * 2;

        if (new_capacity < array->capacity ||
            new_capacity > SIZE_MAX / sizeof(*array->items)) {
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

static int split_regex(const char *input, const char *delimiter_pattern,
                       StringArray *result)
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

    const char *cursor = input;
    size_t remaining = strlen(input);

    while (remaining > 0) {
        regmatch_t match;
        int status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (append_token(result, cursor, remaining) != 0) {
                regfree(&regex);
                free_string_array(result);
                return -1;
            }
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo < match.rm_so) {
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        size_t match_start = (size_t)match.rm_so;
        size_t match_end = (size_t)match.rm_eo;

        if (match_end > remaining || match_end == match_start) {
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        if (match_start > 0 &&
            append_token(result, cursor, match_start) != 0) {
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        cursor += match_end;
        remaining -= match_end;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char input[] = "one,two;three four\tfive";
    const char delimiters[] = "[,;[:space:]]+";
    StringArray tokens = {NULL, 0, 0};

    if (split_regex(input, delimiters, &tokens) != 0) {
        fputs("Failed to split string\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < tokens.count; ++i) {
        puts(tokens.items[i]);
    }

    free_string_array(&tokens);
    return EXIT_SUCCESS;
}
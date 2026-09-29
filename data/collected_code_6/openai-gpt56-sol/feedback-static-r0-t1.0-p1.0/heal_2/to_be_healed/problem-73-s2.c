#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

typedef struct {
    char **items;
    size_t count;
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
}

static int append_token(StringArray *array, const char *start, size_t length)
{
    if (array == NULL || (start == NULL && length != 0)) {
        return -1;
    }

    if (length == SIZE_MAX ||
        array->count >= SIZE_MAX / sizeof(*array->items)) {
        return -1;
    }

    char *token = malloc(length + 1);
    if (token == NULL) {
        return -1;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, start, length);
    }
    token[length] = '\0';

    size_t new_count = array->count + 1;
    char **new_items = realloc(array->items,
                               new_count * sizeof(*new_items));
    if (new_items == NULL) {
        free(token);
        return -1;
    }

    new_items[array->count] = token;
    array->items = new_items;
    array->count = new_count;
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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_length = strlen(input);
    size_t offset = 0;

    regex_t regex;
    if (regcomp(&regex, delimiter_pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    while (offset < input_length) {
        regmatch_t match;
        int status = regexec(&regex, input + offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (append_token(result, input + offset,
                             input_length - offset) != 0) {
                regfree(&regex);
                free_string_array(result);
                return -1;
            }
            break;
        }

        if (status != 0 || match.rm_so < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<match.rm_so' is not redundant
             */
            match.rm_eo < match.rm_so) {
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        /* Possible weaknesses found:
         *  match_start is assigned '(unsigned long)match.rm_so' here.
         */
        size_t match_start = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'match_end=(unsigned long)match.rm_eo', assigned value is less than symbolic=match_start-1
         */
        size_t match_end = (size_t)match.rm_eo;

        /* Possible weaknesses found:
         *  Condition 'match_end==match_start' is always false
         *  Condition 'match_end==match_start' is always false [knownConditionTrueFalse]
         */
        if (match_end > input_length - offset || match_end == match_start) {
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        if (match_start > 0 &&
            append_token(result, input + offset, match_start) != 0) {
            regfree(&regex);
            free_string_array(result);
            return -1;
        }

        offset += match_end;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char input[] = "one,two;three four\tfive";
    const char delimiters[] = "[,;[:space:]]+";
    StringArray tokens = {NULL, 0};

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
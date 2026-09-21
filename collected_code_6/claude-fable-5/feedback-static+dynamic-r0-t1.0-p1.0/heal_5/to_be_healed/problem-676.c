#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

char *remove_non_alphanumeric(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t input_len;
    size_t result_pos;
    size_t result_capacity;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    result_capacity = input_len + 1;
    result = malloc(result_capacity);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:alnum:]]+", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    result_pos = 0;
    cursor = input;

    while (*cursor != '\0') {
        size_t match_len;
        size_t remaining_space;

        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret != 0) {
            break;
        }
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            break;
        }

        match_len = (size_t)(match.rm_eo - match.rm_so);

        if (result_pos >= result_capacity) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        remaining_space = result_capacity - 1 - result_pos;

        if (match_len > remaining_space) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_pos, cursor + match.rm_so, match_len);
        result_pos += match_len;
        cursor += match.rm_eo;
    }

    result[result_pos] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "Hello, World! 123",
        "a@b#c$d%e^1&2*3",
        "!!!???...",
        "AlreadyClean123"
    };
    size_t count;
    size_t i;

    count = sizeof(test_strings) / sizeof(test_strings[0]);

    for (i = 0; i < count; i++) {
        char *cleaned = remove_non_alphanumeric(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string: %s\n",
                    test_strings[i]);
            return EXIT_FAILURE;
        }
        printf("Original: %s\nCleaned:  %s\n\n",
               test_strings[i], cleaned);
        free(cleaned);
    }

    return EXIT_SUCCESS;
}
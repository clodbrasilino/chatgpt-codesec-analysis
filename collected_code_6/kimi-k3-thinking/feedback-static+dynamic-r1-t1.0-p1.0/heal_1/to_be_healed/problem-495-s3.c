#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_len;
    size_t capacity;
    int status;

    if (input == NULL) {
        return NULL;
    }

    status = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    capacity = strlen(input) + 1;
    result = malloc(capacity);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    result_len = 0;

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(cursor);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, remaining);
            result_len += remaining;
            break;
        }

        if (status != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_eo < match.rm_so) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, cursor, (size_t)match.rm_so);
        result_len += (size_t)match.rm_so;
        cursor += match.rm_eo;

        if (match.rm_eo == 0) {
            result[result_len] = *cursor;
            result_len++;
            cursor++;
        }
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "HELLOworldTHISisATEST123abcXYZ",
        "nolowercaseHERE",
        "onlylower",
        "12345!@#$%",
        ""
    };
    size_t count = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < count; i++) {
        char *cleaned = remove_lowercase_substrings(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Error: failed to process string %zu\n", i);
            return EXIT_FAILURE;
        }
        printf("Original: \"%s\"\n", test_strings[i]);
        printf("Cleaned:  \"%s\"\n\n", cleaned);
        free(cleaned);
    }

    return EXIT_SUCCESS;
}
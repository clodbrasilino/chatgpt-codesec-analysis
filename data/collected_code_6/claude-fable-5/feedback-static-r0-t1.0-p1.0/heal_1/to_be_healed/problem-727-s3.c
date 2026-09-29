#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alnum(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t result_len;
    size_t input_len;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:alnum:]]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    result = malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    result_len = 0;
    cursor = input;

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, cursor + match.rm_so,
               (size_t)(match.rm_eo - match.rm_so));
        result_len += (size_t)(match.rm_eo - match.rm_so);
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "Hello, World! 123",
        "a-b_c=d+e",
        "!!!@@@###",
        "NoSpecialChars2024"
    };
    size_t count;
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'cleaned' can be reduced. [variableScope]
     */
    char *cleaned;

    count = sizeof(test_strings) / sizeof(test_strings[0]);

    for (i = 0; i < count; i++) {
        cleaned = remove_non_alnum(test_strings[i]);
        if (cleaned == NULL) {
            fprintf(stderr, "Failed to process string: %s\n", test_strings[i]);
            return EXIT_FAILURE;
        }
        if (printf("Original: %s\nCleaned:  %s\n\n",
                   test_strings[i], cleaned) < 0) {
            free(cleaned);
            return EXIT_FAILURE;
        }
        free(cleaned);
    }

    return EXIT_SUCCESS;
}
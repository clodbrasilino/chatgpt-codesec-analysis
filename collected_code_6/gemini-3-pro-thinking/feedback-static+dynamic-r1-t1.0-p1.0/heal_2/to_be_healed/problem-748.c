#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 8192

char *insert_spaces_before_caps(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, MAX_INPUT_LEN);

    char *safe_input = (char *)malloc(input_len + 1);
    if (safe_input == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(safe_input, input, input_len);
    safe_input[input_len] = '\0';

    regex_t regex;
    if (regcomp(&regex, "([^ \t\n\r])([A-Z])", REG_EXTENDED) != 0) {
        free(safe_input);
        return NULL;
    }

    size_t max_len = (input_len * 2) + 1;
    char *result = (char *)malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        free(safe_input);
        return NULL;
    }

    const char *cursor = safe_input;
    char *res_cursor = result;
    size_t remaining = max_len;
    regmatch_t pmatch[3];

    while (regexec(&regex, cursor, 3, pmatch, 0) == 0) {
        size_t copy_len = (size_t)pmatch[1].rm_eo;

        if (copy_len >= remaining) {
            break;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(res_cursor, cursor, copy_len);
        res_cursor += copy_len;
        remaining -= copy_len;

        if (remaining > 1) {
            *res_cursor = ' ';
            res_cursor++;
            remaining--;
        }

        cursor += pmatch[2].rm_so;
    }

    if (remaining > 0) {
        snprintf(res_cursor, remaining, "%s", cursor);
    }

    regfree(&regex);
    free(safe_input);

    return result;
}

int main(void) {
    const char *test_strings[] = {
        "HelloWorld",
        "ThisIsATest",
        "Already Has Spaces",
        "startsLowercase",
        "ParseURL",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        char *formatted = insert_spaces_before_caps(test_strings[i]);
        if (formatted != NULL) {
            printf("%s\n", formatted);
            free(formatted);
        } else {
            fprintf(stderr, "Error processing string: %s\n", test_strings[i]);
        }
    }

    return 0;
}
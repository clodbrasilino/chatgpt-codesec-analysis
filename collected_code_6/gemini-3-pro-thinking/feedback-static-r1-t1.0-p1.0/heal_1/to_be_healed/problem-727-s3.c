#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *filter_alnum_regex(const char *input);

char *filter_alnum_regex(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[a-zA-Z0-9]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    char *dest = result;
    regmatch_t match[1];

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        size_t len = match[0].rm_eo - match[0].rm_so;
        if (len == 0) {
            break;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dest, cursor + match[0].rm_so, len);
        dest += len;
        cursor += match[0].rm_eo;
    }
    *dest = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_str = "Hello, World! 123 @#Test.";
    char *cleaned_str = filter_alnum_regex(test_str);

    if (cleaned_str != NULL) {
        printf("%s\n", cleaned_str);
        free(cleaned_str);
    } else {
        fprintf(stderr, "Processing failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase(const char *input);

char *remove_lowercase(const char *input) {
    if (!input) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[a-z]+", REG_EXTENDED) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *result = malloc(input_len + 1);
    if (!result) {
        regfree(&regex);
        return NULL;
    }

    const char *cursor = input;
    char *out_cursor = result;
    regmatch_t match;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t prefix_len = (size_t)match.rm_so;
        if (prefix_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(out_cursor, cursor, prefix_len);
            out_cursor += prefix_len;
        }
        cursor += match.rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining_len = strlen(cursor);
    if (remaining_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(out_cursor, cursor, remaining_len);
        out_cursor += remaining_len;
    }
    *out_cursor = '\0';

    regfree(&regex);

    char *shrunk_result = realloc(result, (size_t)(out_cursor - result + 1));
    if (shrunk_result != NULL) {
        return shrunk_result;
    }

    return result;
}

int main(void) {
    const char *test_string = "HELLO world THIS is A test STRING 123!";
    char *cleaned_string = remove_lowercase(test_string);
    
    if (cleaned_string) {
        printf("%s\n", cleaned_string);
        free(cleaned_string);
    } else {
        fprintf(stderr, "Failed to process the string.\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
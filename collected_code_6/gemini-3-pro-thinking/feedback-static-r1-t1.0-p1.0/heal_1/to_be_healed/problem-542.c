#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_characters_with_colon(const char *input) {
    regex_t regex;
    int ret;
    size_t len;
    char *result;
    const char *cursor;
    char *out_cursor;
    regmatch_t pmatch[1];

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    result = (char *)malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    out_cursor = result;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t prefix_len;

        if (pmatch[0].rm_so < 0 || pmatch[0].rm_eo < 0) {
            break;
        }

        prefix_len = (size_t)pmatch[0].rm_so;

        if (prefix_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(out_cursor, cursor, prefix_len);
            out_cursor += prefix_len;
        }

        *out_cursor = ':';
        out_cursor++;

        cursor += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(out_cursor, cursor);
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_string = "This is a test, with spaces. and commas, and dots.";
    char *replaced_string;

    replaced_string = replace_characters_with_colon(test_string);

    if (replaced_string != NULL) {
        printf("%s\n", replaced_string);
        free(replaced_string);
        replaced_string = NULL;
    }

    return 0;
}
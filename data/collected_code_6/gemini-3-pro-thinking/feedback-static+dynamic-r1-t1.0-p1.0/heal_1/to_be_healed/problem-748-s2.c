#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* insert_spaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    size_t max_len = (input_len * 2) + 1;
    char* result = (char*)malloc(max_len);

    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    result[0] = '\0';
    char* out_ptr = result;
    const char* cursor = input;
    regmatch_t match[1];

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        size_t prefix_len = match[0].rm_so;

        if (prefix_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(out_ptr, cursor, prefix_len);
            out_ptr += prefix_len;
        }

        const char* match_pos = cursor + match[0].rm_so;

        if (match_pos > input && *(match_pos - 1) != ' ') {
            *out_ptr = ' ';
            out_ptr++;
        }

        *out_ptr = *match_pos;
        out_ptr++;

        cursor += match[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(out_ptr, cursor);
    regfree(&regex);

    return result;
}

int main(void) {
    const char* test_str = "thisIsATestStringForRegex";
    char* formatted_str = insert_spaces(test_str);

    if (formatted_str != NULL) {
        printf("%s\n", formatted_str);
        free(formatted_str);
    } else {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    return 0;
}
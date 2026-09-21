#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *replace_chars_with_colon(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int comp_res = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (comp_res != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    char *output = (char *)malloc(len + 1);
    if (output == NULL) {
        regfree(&regex);
        return NULL;
    }

    regmatch_t pmatch[1];
    const char *cursor = input;
    char *out_cursor = output;

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t prefix_len = pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(out_cursor, cursor, prefix_len);
        out_cursor += prefix_len;
        
        *out_cursor = ':';
        out_cursor++;
        
        cursor += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(out_cursor, cursor);
    regfree(&regex);

    return output;
}

int main(void) {
    const char *test_str = "Hello, world. This is a test string.";
    char *result = replace_chars_with_colon(test_str);

    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error processing string\n");
        return 1;
    }

    return 0;
}
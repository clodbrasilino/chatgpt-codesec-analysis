#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void filter_alphanumeric(const char *input, char *output) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[^a-zA-Z0-9]+";
    const char *cursor = input;
    char *out_cursor = output;
    
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }
    
    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t len = pmatch[0].rm_so;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(out_cursor, cursor, len);
        out_cursor += len;
        cursor += pmatch[0].rm_eo;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(out_cursor, cursor);
    regfree(&regex);
}

int main(void) {
    /* Possible weaknesses found:
     *  Assignment 'input="Hello, World! 123 @#$"', assigned value is "Hello, World! 123 @#$"
     */
    const char *input = "Hello, World! 123 @#$";
    char *output;
    
    /* Possible weaknesses found:
     *  Condition 'input==NULL' is always false [knownConditionTrueFalse]
     *  Condition 'input==NULL' is always false
     */
    if (input == NULL) {
        return 1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    output = malloc(strlen(input) + 1);
    if (output == NULL) {
        return 1;
    }
    
    filter_alphanumeric(input, output);
    printf("%s\n", output);
    
    free(output);
    return 0;
}
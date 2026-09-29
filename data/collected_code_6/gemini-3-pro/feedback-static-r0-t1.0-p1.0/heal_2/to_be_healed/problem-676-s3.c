#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void filter_alphanumeric(const char *input, char *output, size_t out_size) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[^a-zA-Z0-9]+";
    const char *cursor = input;
    char *out_cursor = output;
    size_t remaining = out_size;

    if (input == NULL || output == NULL || out_size == 0) {
        if (output != NULL && out_size > 0) {
            output[0] = '\0';
        }
        return;
    }

    output[0] = '\0';

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return;
    }

    while (regexec(&regex, cursor, 1, pmatch, 0) == 0) {
        size_t len = pmatch[0].rm_so;
        
        if (len >= remaining) {
            len = remaining - 1;
        }
        
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(out_cursor, cursor, len);
            out_cursor += len;
            remaining -= len;
        }
        
        cursor += pmatch[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t end_len = strlen(cursor);
    if (end_len >= remaining) {
        end_len = remaining - 1;
    }
    
    if (end_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(out_cursor, cursor, end_len);
        out_cursor += end_len;
    }
    
    *out_cursor = '\0';
    
    regfree(&regex);
}

int main(void) {
    const char *input = "Hello, World! 123 @#$";
    char *output;
    size_t input_size;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_size = strlen(input) + 1;
    
    output = malloc(input_size);
    if (output == NULL) {
        return 1;
    }

    filter_alphanumeric(input, output, input_size);
    printf("%s\n", output);

    free(output);
    return 0;
}
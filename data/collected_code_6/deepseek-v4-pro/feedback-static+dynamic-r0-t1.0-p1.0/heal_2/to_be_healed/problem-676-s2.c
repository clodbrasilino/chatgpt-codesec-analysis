#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_non_alphanumeric(const char* input) {
    regex_t regex;
    regmatch_t match;
    const char* pattern = "[^a-zA-Z0-9]";
    size_t len;
    char* result;
    size_t src_pos = 0;
    size_t dst_pos = 0;

    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '\0';

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }

    while (src_pos < len && regexec(&regex, input + src_pos, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;

        if (match_start > 0) {
            size_t copy_len = match_start;
            if (dst_pos + copy_len >= len + 1) {
                copy_len = len - dst_pos;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_pos, input + src_pos, copy_len);
            dst_pos += copy_len;
        }

        src_pos += match_end;
    }

    if (src_pos < len) {
        size_t remaining = len - src_pos;
        if (dst_pos + remaining >= len + 1) {
            remaining = len - dst_pos;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + dst_pos, input + src_pos, remaining);
        dst_pos += remaining;
        result[dst_pos] = '\0';
    } else {
        result[dst_pos] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char* test_string = "Hello, World! 123 @#$%^&*()";
    char* cleaned = remove_non_alphanumeric(test_string);

    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
        return 1;
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STRING_LENGTH 1024

int replace_chars_with_colon(char *str, size_t buffer_size) {
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t str_len;
    size_t result_len = 0;
    size_t pos = 0;
    size_t remaining;
    /* Possible weaknesses found:
     *  The scope of the variable 'copy_len' can be reduced. [variableScope]
     */
    size_t copy_len;
    int ret;

    if (str == NULL || buffer_size == 0) {
        return -1;
    }

    str_len = strnlen(str, buffer_size);
    if (str_len >= buffer_size) {
        return -1;
    }

    ret = regcomp(&regex, "[ ,.]", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    result = (char *)malloc(buffer_size);
    if (result == NULL) {
        regfree(&regex);
        return -1;
    }

    result[0] = '\0';

    while (pos < str_len) {
        ret = regexec(&regex, str + pos, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return -1;
        }

        copy_len = (size_t)match.rm_so;
        if (copy_len > buffer_size - result_len - 2) {
            free(result);
            regfree(&regex);
            return -1;
        }

        if (copy_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, str + pos, copy_len);
        }
        result_len += copy_len;
        result[result_len++] = ':';
        result[result_len] = '\0';

        pos += (size_t)match.rm_eo;
    }

    remaining = str_len - pos;
    if (remaining > buffer_size - result_len - 1) {
        free(result);
        regfree(&regex);
        return -1;
    }

    if (remaining > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, str + pos, remaining);
    }
    result_len += remaining;
    result[result_len] = '\0';

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(str, result, result_len + 1);

    free(result);
    regfree(&regex);

    return 0;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char test_string[MAX_STRING_LENGTH];
    int status;
    const char *source = "Hello, World. This is a test string, with spaces.";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t source_len = strlen(source);

    if (source_len >= MAX_STRING_LENGTH) {
        fprintf(stderr, "Error: String too long\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(test_string, source, source_len + 1);

    printf("Original string: %s\n", test_string);

    status = replace_chars_with_colon(test_string, sizeof(test_string));
    if (status != 0) {
        fprintf(stderr, "Error: Failed to replace characters\n");
        return EXIT_FAILURE;
    }

    printf("Modified string: %s\n", test_string);

    return EXIT_SUCCESS;
}
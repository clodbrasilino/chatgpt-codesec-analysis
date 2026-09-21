#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase(const char *input) {
    regex_t regex;
    int ret;
    size_t input_len;
    char *result;
    char *result_ptr;
    const char *cursor;
    regmatch_t match[1];
    /* Possible weaknesses found:
     *  The scope of the variable 'prefix_len' can be reduced. [variableScope]
     */
    size_t prefix_len;
    size_t remaining_len;

    if (input == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    result[0] = '\0';
    result_ptr = result;
    cursor = input;

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        prefix_len = (size_t)match[0].rm_so;
        if (prefix_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result_ptr, cursor, prefix_len);
            result_ptr += prefix_len;
        }
        cursor += match[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    remaining_len = strlen(cursor);
    if (remaining_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result_ptr, cursor, remaining_len);
        result_ptr += remaining_len;
    }
    *result_ptr = '\0';

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_str = "HelloWorld123ThisIsATest";
    char *processed_str = remove_lowercase(test_str);

    if (processed_str != NULL) {
        printf("%s\n", processed_str);
        free(processed_str);
    } else {
        fprintf(stderr, "Failed to process string.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
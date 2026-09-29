#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'google_assistant', got Google_assistant
  *  test case 2 failed: expected 'quad_core', got Quad_core
  *  test case 1 failed: expected 'chrome_cast', got Chrome_cast
  */

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t max_len = strlen(camel_str) * 2 + 1;
    char *temp1 = malloc(max_len);
    char *temp2 = malloc(max_len);
    if (temp1 == NULL || temp2 == NULL) {
        free(temp1);
        free(temp2);
        regfree(&regex);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(temp1, camel_str, max_len - 1);
    temp1[max_len - 1] = '\0';

    regmatch_t matches[3];
    while (regexec(&regex, temp1, 3, matches, 0) == 0) {
        size_t prefix_len = matches[1].rm_so;
        size_t lower_len = matches[1].rm_eo - matches[1].rm_so;
        size_t upper_len = matches[2].rm_eo - matches[2].rm_so;
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t suffix_len = strlen(temp1 + matches[2].rm_eo);

        if (prefix_len + lower_len + 1 + upper_len + suffix_len >= max_len) {
            free(temp1);
            free(temp2);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp2, temp1, prefix_len);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp2 + prefix_len, temp1 + matches[1].rm_so, lower_len);
        temp2[prefix_len + lower_len] = '_';
        char upper_char = temp1[matches[2].rm_so];
        temp2[prefix_len + lower_len + 1] = upper_char + 32;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp2 + prefix_len + lower_len + 2, temp1 + matches[2].rm_eo, suffix_len);
        temp2[prefix_len + lower_len + 1 + upper_len + suffix_len] = '\0';

        char *swap = temp1;
        temp1 = temp2;
        temp2 = swap;
    }

    regfree(&regex);
    free(temp2);

    return temp1;
}

int main(void) {
    const char *input = "convertCamelCaseToSnakeCase";
    char *result = camel_to_snake(input);
    
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }
    
    return 0;
}
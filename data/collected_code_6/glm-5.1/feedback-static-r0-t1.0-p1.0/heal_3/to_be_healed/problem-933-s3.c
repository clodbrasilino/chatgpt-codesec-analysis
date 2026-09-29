#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    size_t input_len = 0;
    while (camel_str[input_len] != '\0') {
        input_len++;
    }

    if (input_len == 0) {
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([a-z0-9])([A-Z])", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'max_len=input_len*2+1', assigned value is greater than 0
     */
    size_t max_len = input_len * 2 + 1;
    char *temp1 = malloc(max_len);
    char *temp2 = malloc(max_len);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (temp1 == NULL || temp2 == NULL) {
        free(temp1);
        free(temp2);
        regfree(&regex);
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'max_len>0' is always true [knownConditionTrueFalse]
     *  Condition 'max_len>0' is always true
     */
    if (max_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(temp1, camel_str, input_len + 1);
    }

    size_t current_len = input_len;
    size_t offset = 0;

    while (offset < current_len) {
        if (regexec(&regex, temp1 + offset, 3, (regmatch_t[3]){0}, 0) == 0) {
            regmatch_t matches[3];
            regexec(&regex, temp1 + offset, 3, matches, 0);
            size_t prefix_len = offset + matches[2].rm_so;
            size_t suffix_len = current_len - (offset + matches[2].rm_eo);

            if (prefix_len <= max_len && (prefix_len + 2) <= max_len && (prefix_len + 2 + suffix_len) < max_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(temp2, temp1, prefix_len);
                temp2[prefix_len] = '_';
                temp2[prefix_len + 1] = tolower((unsigned char)temp1[prefix_len]);
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(temp2 + prefix_len + 2, temp1 + prefix_len + 1, suffix_len);
                current_len = prefix_len + 2 + suffix_len;
                temp2[current_len] = '\0';

                if (current_len + 1 <= max_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(temp1, temp2, current_len + 1);
                }
            }
            offset = prefix_len + 2;
        } else {
            break;
        }
    }

    regfree(&regex);

    size_t final_len = current_len + 1;
    char *final_str = malloc(final_len);
    if (final_str == NULL) {
        free(temp1);
        free(temp2);
        return NULL;
    }

    if (final_len <= max_len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(final_str, temp1, final_len);
    }

    free(temp1);
    free(temp2);

    return final_str;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camel_case_string>\n", argv[0]);
        return 1;
    }

    char *snake_str = camel_to_snake(argv[1]);
    if (snake_str == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }

    printf("%s\n", snake_str);

    free(snake_str);
    return 0;
}
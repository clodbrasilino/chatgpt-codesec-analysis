#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_whitespace(const char *input, size_t input_len) {
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_len;
    size_t copy_len;
    size_t remaining;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    result = malloc(input_len + 1);
    if (result == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[[:space:]]", REG_EXTENDED);
    if (ret != 0) {
        free(result);
        return NULL;
    }

    cursor = input;
    result_len = 0;
    remaining = input_len;

    /* Possible weaknesses found:
     *  Assuming that condition 'remaining>0' is not redundant
     */
    while (remaining > 0) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             *  copy_len is assigned 'remaining' here.
             */
            copy_len = remaining;
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (result_len + copy_len > input_len) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             *  Condition 'copy_len>0' is always true [knownConditionTrueFalse]
             *  Condition 'copy_len>0' is always true
             */
            if (copy_len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, copy_len);
                result_len += copy_len;
            }
            break;
        } else if (ret != 0) {
            regfree(&regex);
            free(result);
            return NULL;
        }

        copy_len = (size_t)match.rm_so;
        if (result_len + copy_len > input_len || copy_len > remaining) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        if (copy_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, cursor, copy_len);
            result_len += copy_len;
        }
        
        if ((size_t)match.rm_eo > remaining) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        cursor += match.rm_eo;
        remaining -= (size_t)match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);

    return result;
}

int main(void) {
    const char *test_string = "Hello World \t This is a test \n string";
    char *cleaned;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    cleaned = remove_whitespace(test_string, strlen(test_string));
    if (cleaned == NULL) {
        fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);

    return EXIT_SUCCESS;
}
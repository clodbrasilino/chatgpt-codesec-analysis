#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_lowercase_substrings(const char *input, size_t max_len)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    char *result;
    size_t result_len;
    size_t input_len;
    size_t copy_len;
    size_t remaining;
    int ret;

    if (input == NULL || max_len == 0) {
        return NULL;
    }

    ret = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    input_len = strnlen(input, max_len);
    result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    cursor = input;
    result_len = 0;

    while (*cursor != '\0' && (size_t)(cursor - input) < input_len) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            remaining = input_len - (size_t)(cursor - input);
            copy_len = strnlen(cursor, remaining);
            if (copy_len > remaining) {
                copy_len = remaining;
            }
            /* Possible weaknesses found:
             *  Assuming that condition 'result_len+copy_len>input_len' is not redundant
             */
            if (result_len + copy_len > input_len) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            if (copy_len > 0) {
                /* Possible weaknesses found:
                 *  Condition 'result_len+copy_len<=input_len' is always true
                 *  Condition 'result_len+copy_len<=input_len' is always true [knownConditionTrueFalse]
                 */
                if (result_len + copy_len <= input_len) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result + result_len, cursor, copy_len);
                    result_len += copy_len;
                } else {
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
            }
            break;
        } else if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        copy_len = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assuming that condition 'result_len+copy_len>input_len' is not redundant
         */
        if (result_len + copy_len > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (copy_len > 0) {
            /* Possible weaknesses found:
             *  Condition 'result_len+copy_len<=input_len' is always true
             *  Condition 'result_len+copy_len<=input_len' is always true [knownConditionTrueFalse]
             */
            if (result_len + copy_len <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_len, cursor, copy_len);
                result_len += copy_len;
            } else {
                free(result);
                regfree(&regex);
                return NULL;
            }
        }
        cursor += match.rm_eo;
    }

    result[result_len] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    const char *test_string = "HelloWorldTESTString123abcXYZ";
    char *processed;

    processed = remove_lowercase_substrings(test_string, strnlen(test_string, 1024) + 1);
    if (processed == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", test_string);
    printf("Processed: %s\n", processed);

    free(processed);
    return EXIT_SUCCESS;
}
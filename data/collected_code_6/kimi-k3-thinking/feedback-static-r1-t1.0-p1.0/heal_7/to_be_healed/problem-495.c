#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 4096

char *remove_lowercase_substrings(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result = NULL;
    char *bounded_input = NULL;
    size_t result_len = 0;
    size_t result_capacity;
    size_t bounded_input_capacity;
    size_t input_len;
    size_t pos = 0;
    int status;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH + 1);
    if (input_len > MAX_INPUT_LENGTH || input_len == SIZE_MAX) {
        return NULL;
    }

    status = regcomp(&regex, "[a-z]+", REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'bounded_input_capacity=input_len+1', assigned value is greater than 0
     */
    bounded_input_capacity = input_len + 1;
    bounded_input = malloc(bounded_input_capacity);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (bounded_input == NULL) {
        regfree(&regex);
        return NULL;
    }

    if (input_len > 0) {
        /* Possible weaknesses found:
         *  Condition 'bounded_input_capacity<1' is always false
         *  Condition 'bounded_input_capacity<1' is always false [knownConditionTrueFalse]
         */
        if (bounded_input_capacity < 1 || input_len > bounded_input_capacity - 1) {
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(bounded_input, input, input_len);
    }
    bounded_input[input_len] = '\0';

    result_capacity = input_len + 1;
    result = malloc(result_capacity);
    if (result == NULL) {
        free(bounded_input);
        regfree(&regex);
        return NULL;
    }

    while (pos < input_len) {
        size_t copy_len;
        size_t remaining;

        status = regexec(&regex, bounded_input + pos, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }
        if (status != 0) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }

        if (match.rm_so < 0 || match.rm_eo <= 0 || match.rm_eo < match.rm_so) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }

        remaining = input_len - pos;
        if ((size_t)match.rm_so > remaining || (size_t)match.rm_eo > remaining) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }

        copy_len = (size_t)match.rm_so;
        if (copy_len > 0) {
            /* Possible weaknesses found:
             *  Assuming that condition 'result_len>=result_capacity' is not redundant
             */
            if (result_len >= result_capacity ||
                /* Possible weaknesses found:
                 *  Condition 'result_capacity-result_len<1' is always false [knownConditionTrueFalse]
                 *  Condition 'result_capacity-result_len<1' is always false
                 */
                result_capacity - result_len < 1 ||
                copy_len > result_capacity - result_len - 1) {
                free(result);
                free(bounded_input);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_len, bounded_input + pos, copy_len);
            result_len += copy_len;
        }
        pos += (size_t)match.rm_eo;
    }

    if (pos < input_len) {
        size_t copy_len = input_len - pos;

        /* Possible weaknesses found:
         *  Assuming that condition 'result_len>=result_capacity' is not redundant
         */
        if (result_len >= result_capacity ||
            /* Possible weaknesses found:
             *  Condition 'result_capacity-result_len<1' is always false [knownConditionTrueFalse]
             *  Condition 'result_capacity-result_len<1' is always false
             */
            result_capacity - result_len < 1 ||
            copy_len > result_capacity - result_len - 1) {
            free(result);
            free(bounded_input);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_len, bounded_input + pos, copy_len);
        result_len += copy_len;
    }

    if (result_len >= result_capacity) {
        free(result);
        free(bounded_input);
        regfree(&regex);
        return NULL;
    }
    result[result_len] = '\0';

    free(bounded_input);
    regfree(&regex);

    return result;
}

int main(void)
{
    const char *test_strings[] = {
        "HELLOworldTHISisTESTingSTRING",
        "alllowercase",
        "ALLUPPERCASE",
        "Mix3dW0rdsHere",
        ""
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        char *result = remove_lowercase_substrings(test_strings[i]);
        if (result == NULL) {
            fprintf(stderr, "Failed to process string at index %zu\n", i);
            return EXIT_FAILURE;
        }

        printf("Original: \"%s\"\n", test_strings[i]);
        printf("Modified: \"%s\"\n\n", result);

        free(result);
    }

    return EXIT_SUCCESS;
}
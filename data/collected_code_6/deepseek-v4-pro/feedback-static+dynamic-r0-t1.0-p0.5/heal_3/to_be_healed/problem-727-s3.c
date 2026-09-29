#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *remove_non_alphanumeric(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    char *result = (char *)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t result_index = 0;
    regmatch_t match;
    const char *cursor = input;

    while (regexec(&regex, cursor, 1, &match, 0) == 0) {
        size_t match_start = match.rm_so;
        size_t match_end = match.rm_eo;

        if (match_start > 0) {
            /* Possible weaknesses found:
             *  Assuming that condition 'result_index+match_start>input_len' is not redundant
             */
            if (result_index + match_start > input_len) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            /* Possible weaknesses found:
             *  Condition 'result_index+match_start<=input_len' is always true
             *  Condition 'result_index+match_start<=input_len' is always true [knownConditionTrueFalse]
             */
            if (result_index + match_start <= input_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_index, cursor, match_start);
                result_index += match_start;
            }
        }

        cursor += match_end;
        if (*cursor == '\0') {
            break;
        }
    }

    if (*cursor != '\0') {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t remaining = strlen(cursor);
        /* Possible weaknesses found:
         *  Assuming that condition 'result_index+remaining>input_len' is not redundant
         */
        if (result_index + remaining > input_len) {
            regfree(&regex);
            free(result);
            return NULL;
        }
        /* Possible weaknesses found:
         *  Condition 'result_index+remaining<=input_len' is always true
         *  Condition 'result_index+remaining<=input_len' is always true [knownConditionTrueFalse]
         */
        if (result_index + remaining <= input_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_index, cursor, remaining);
            result_index += remaining;
        }
    }

    result[result_index] = '\0';
    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "Hello, World! 123 @#$%^&*()";
    char *cleaned = remove_non_alphanumeric(test_string);
    
    if (cleaned != NULL) {
        printf("Original: %s\n", test_string);
        printf("Cleaned: %s\n", cleaned);
        free(cleaned);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
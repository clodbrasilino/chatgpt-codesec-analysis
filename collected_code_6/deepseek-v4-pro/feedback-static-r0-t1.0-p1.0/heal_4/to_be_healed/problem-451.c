#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* remove_whitespaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }
    
    regex_t regex;
    int reti = regcomp(&regex, "[[:space:]]", 0);
    if (reti != 0) {
        return NULL;
    }
    
    size_t input_len = strnlen(input, 8192);
    if (input_len == 8192 && input[8192] != '\0') {
        regfree(&regex);
        return NULL;
    }
    
    char* result = (char*)malloc(input_len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    
    size_t result_index = 0;
    size_t result_size = input_len + 1;
    regmatch_t match;
    const char* cursor = input;
    const char* input_end = input + input_len;
    
    while (cursor < input_end && *cursor != '\0' && regexec(&regex, cursor, 1, &match, 0) == 0) {
        if (match.rm_so > 0) {
            /* Possible weaknesses found:
             *  Assuming that condition 'result_index+(unsigned long)match.rm_so>=result_size' is not redundant
             */
            if (result_index + (size_t)match.rm_so >= result_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             *  Condition 'result_index+(unsigned long)match.rm_so<=result_size' is always true
             *  Condition 'result_index+(unsigned long)match.rm_so<=result_size' is always true [knownConditionTrueFalse]
             */
            size_t copy_len = (result_index + (size_t)match.rm_so <= result_size) ? (size_t)match.rm_so : result_size - result_index - 1;
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + result_index, cursor, copy_len);
            result_index += copy_len;
        }
        cursor += match.rm_eo;
        if (cursor > input_end) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (match.rm_eo == 0) {
            if (result_index + 1 >= result_size) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            if (cursor < input_end) {
                result[result_index++] = *cursor;
                if (*cursor != '\0') {
                    cursor++;
                }
            }
        }
    }
    
    if (cursor < input_end && *cursor != '\0') {
        size_t remaining = strnlen(cursor, input_end - cursor);
        /* Possible weaknesses found:
         *  Assuming that condition 'result_index+remaining>=result_size' is not redundant
         */
        if (result_index + remaining >= result_size) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         *  Condition 'result_index+remaining<=result_size' is always true [knownConditionTrueFalse]
         *  Condition 'result_index+remaining<=result_size' is always true
         */
        size_t copy_len = (result_index + remaining <= result_size) ? remaining : result_size - result_index - 1;
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + result_index, cursor, copy_len);
        result_index += copy_len;
    }
    
    if (result_index >= result_size) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    result[result_index] = '\0';
    regfree(&regex);
    
    return result;
}

int main(void) {
    const char* test_string = "Hello World\tfrom\nC programming";
    char* cleaned = remove_whitespaces(test_string);
    
    if (cleaned != NULL) {
        printf("Original: '%s'\n", test_string);
        printf("Cleaned: '%s'\n", cleaned);
        free(cleaned);
    } else {
        printf("Error processing string\n");
    }
    
    return 0;
}
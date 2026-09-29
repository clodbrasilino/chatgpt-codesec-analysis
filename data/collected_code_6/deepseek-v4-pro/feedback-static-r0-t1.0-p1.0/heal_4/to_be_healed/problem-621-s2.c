#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static size_t safe_strlen(const char* str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }
    
    size_t input_len = safe_strlen(input, SIZE_MAX / 20);
    if (input_len >= SIZE_MAX / 20) {
        return NULL;
    }
    
    size_t result_size = input_len * 20 + 1;
    if (result_size < input_len) {
        return NULL;
    }
    char* result = (char*)malloc(result_size);
    if (result == NULL) {
        return NULL;
    }
    
    size_t result_pos = 0;
    size_t i = 0;
    
    while (i < input_len && input[i] != '\0') {
        if (isdigit((unsigned char)input[i])) {
            size_t start = i;
            while (i < input_len && input[i] != '\0' && isdigit((unsigned char)input[i])) {
                i++;
            }
            
            size_t num_len = i - start;
            if (num_len >= 64) {
                free(result);
                return NULL;
            }
            
            if (start + num_len < start || start + num_len > input_len) {
                free(result);
                return NULL;
            }
            
            char* num_str = (char*)malloc(num_len + 1);
            if (num_str == NULL) {
                free(result);
                return NULL;
            }
            
            if (result_size < num_len) {
                free(num_str);
                free(result);
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num_str, input + start, num_len);
            num_str[num_len] = '\0';
            
            errno = 0;
            long long num = strtoll(num_str, NULL, 10);
            free(num_str);
            
            if (errno == ERANGE) {
                free(result);
                return NULL;
            }
            
            long long new_num;
            if (k > 0) {
                if (num > LLONG_MAX - k) {
                    free(result);
                    return NULL;
                }
            } else if (k < 0) {
                if (num < LLONG_MIN - k) {
                    free(result);
                    return NULL;
                }
            }
            new_num = num + k;
            
            char* new_num_str = (char*)malloc(64);
            if (new_num_str == NULL) {
                free(result);
                return NULL;
            }
            
            int written = snprintf(new_num_str, 64, "%lld", new_num);
            if (written < 0 || written >= 64) {
                free(new_num_str);
                free(result);
                return NULL;
            }
            
            size_t new_num_len = (size_t)written;
            /* Possible weaknesses found:
             *  Assuming that condition 'result_pos+new_num_len>=result_size' is not redundant
             */
            if (result_pos + new_num_len < result_pos || result_pos + new_num_len >= result_size) {
                free(new_num_str);
                free(result);
                return NULL;
            }
            
            /* Possible weaknesses found:
             *  Condition 'result_pos+new_num_len<=result_size' is always true [knownConditionTrueFalse]
             *  Condition 'result_pos+new_num_len<=result_size' is always true
             */
            if (result_pos + new_num_len <= result_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + result_pos, new_num_str, new_num_len);
            }
            result_pos += new_num_len;
            free(new_num_str);
        } else {
            if (result_pos >= result_size) {
                free(result);
                return NULL;
            }
            result[result_pos++] = input[i++];
        }
    }
    
    if (result_pos >= result_size) {
        free(result);
        return NULL;
    }
    result[result_pos] = '\0';
    return result;
}

int main(void) {
    const char* test1 = "I have 10 apples and 5 oranges";
    const char* test2 = "Numbers: 1, 2, 3, 100";
    const char* test3 = "No numbers here";
    const char* test4 = "Edge case 999999999999999999";
    const char* test5 = "";
    
    char* result1 = increment_numeric_values(test1, 5);
    char* result2 = increment_numeric_values(test2, -2);
    char* result3 = increment_numeric_values(test3, 10);
    char* result4 = increment_numeric_values(test4, 1);
    char* result5 = increment_numeric_values(test5, 3);
    /* Possible weaknesses found:
     *  Assignment 'result6=increment_numeric_values(NULL,5)', assigned value is 0
     *  Calling function 'increment_numeric_values' returns 0
     */
    char* result6 = increment_numeric_values(NULL, 5);
    
    printf("Original: %s\n", test1);
    printf("Result (+5): %s\n\n", result1 ? result1 : "ERROR");
    
    printf("Original: %s\n", test2);
    printf("Result (-2): %s\n\n", result2 ? result2 : "ERROR");
    
    printf("Original: %s\n", test3);
    printf("Result (+10): %s\n\n", result3 ? result3 : "ERROR");
    
    printf("Original: %s\n", test4);
    printf("Result (+1): %s\n\n", result4 ? result4 : "ERROR");
    
    printf("Original: '%s'\n", test5);
    printf("Result (+3): '%s'\n\n", result5 ? result5 : "ERROR");
    
    printf("Original: NULL\n");
    /* Possible weaknesses found:
     *  Condition 'result6' is always false
     *  Condition 'result6' is always false [knownConditionTrueFalse]
     */
    printf("Result: %s\n", result6 ? result6 : "NULL");
    
    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    
    return 0;
}
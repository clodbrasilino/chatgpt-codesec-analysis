#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

#define MAX_NUM_LEN 1024
#define MAX_NUM_STR_SIZE 64

static size_t safe_strlen(const char *str) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (str[len] != '\0') {
        if (len >= SIZE_MAX / 2) {
            return 0;
        }
        len++;
    }
    return len;
}

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }
    
    size_t input_len = safe_strlen(input);
    if (input_len == 0 && input[0] != '\0') {
        return NULL;
    }
    
    /* Possible weaknesses found:
     *  result_size is assigned 'input_len+1' here.
     */
    size_t result_size = input_len + 1;
    /* Possible weaknesses found:
     *  Condition 'result_size<=input_len' is always false
     *  Condition 'result_size<=input_len' is always false [knownConditionTrueFalse]
     */
    if (result_size <= input_len) {
        return NULL;
    }
    
    char* result = (char*)malloc(result_size);
    if (result == NULL) {
        return NULL;
    }
    
    size_t src_idx = 0;
    size_t dst_idx = 0;
    
    while (src_idx < input_len) {
        if (isdigit((unsigned char)input[src_idx])) {
            size_t num_start = src_idx;
            while (src_idx < input_len && isdigit((unsigned char)input[src_idx])) {
                src_idx++;
            }
            size_t num_len = src_idx - num_start;
            
            if (num_len > MAX_NUM_LEN) {
                free(result);
                return NULL;
            }
            
            if (num_len == 0) {
                continue;
            }
            
            if (num_start > SIZE_MAX - num_len || num_start + num_len > input_len) {
                free(result);
                return NULL;
            }
            
            char* num_str = (char*)malloc(num_len + 1);
            if (num_str == NULL) {
                free(result);
                return NULL;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(num_str, input + num_start, num_len);
            num_str[num_len] = '\0';
            
            errno = 0;
            long long num_val = strtoll(num_str, NULL, 10);
            free(num_str);
            
            if (errno == ERANGE) {
                free(result);
                return NULL;
            }
            
            long long new_val;
            if (k > 0 && num_val > LLONG_MAX - k) {
                free(result);
                return NULL;
            }
            if (k < 0 && num_val < LLONG_MIN - k) {
                free(result);
                return NULL;
            }
            new_val = num_val + k;
            
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char new_num_str[MAX_NUM_STR_SIZE];
            int written = snprintf(new_num_str, sizeof(new_num_str), "%lld", new_val);
            if (written < 0 || (size_t)written >= sizeof(new_num_str)) {
                free(result);
                return NULL;
            }
            
            size_t new_num_len = (size_t)written;
            size_t remaining_len = input_len - src_idx;
            
            if (dst_idx > SIZE_MAX - new_num_len || 
                dst_idx + new_num_len > SIZE_MAX - remaining_len) {
                free(result);
                return NULL;
            }
            
            size_t needed_size = dst_idx + new_num_len + remaining_len + 1;
            if (needed_size <= dst_idx) {
                free(result);
                return NULL;
            }
            
            if (needed_size > result_size) {
                char* temp = (char*)realloc(result, needed_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                result_size = needed_size;
            }
            
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + dst_idx, new_num_str, new_num_len);
            dst_idx += new_num_len;
        } else {
            if (dst_idx >= result_size) {
                if (result_size > SIZE_MAX / 2) {
                    free(result);
                    return NULL;
                }
                size_t new_size = result_size * 2;
                if (new_size <= result_size) {
                    free(result);
                    return NULL;
                }
                char* temp = (char*)realloc(result, new_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                result_size = new_size;
            }
            result[dst_idx++] = input[src_idx++];
        }
    }
    
    if (dst_idx >= result_size) {
        if (result_size > SIZE_MAX - 1) {
            free(result);
            return NULL;
        }
        char* temp = (char*)realloc(result, dst_idx + 1);
        if (temp == NULL) {
            free(result);
            return NULL;
        }
        result = temp;
        result_size = dst_idx + 1;
    }
    result[dst_idx] = '\0';
    
    if (dst_idx + 1 < result_size) {
        char* final_result = (char*)realloc(result, dst_idx + 1);
        if (final_result != NULL) {
            return final_result;
        }
    }
    
    return result;
}

int main(void) {
    const char* test1 = "abc123def456";
    char* result1 = increment_numeric_values(test1, 5);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }
    
    const char* test2 = "1a2b3c";
    char* result2 = increment_numeric_values(test2, 10);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }
    
    const char* test3 = "no numbers here";
    char* result3 = increment_numeric_values(test3, 100);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }
    
    const char* test4 = "123";
    char* result4 = increment_numeric_values(test4, 0);
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }
    
    const char* null_input = NULL;
    /* Possible weaknesses found:
     *  Variable 'result5' can be declared as pointer to const [constVariablePointer]
     *  Assignment 'result5=increment_numeric_values(null_input,5)', assigned value is 0
     *  Calling function 'increment_numeric_values' returns 0
     */
    char* result5 = increment_numeric_values(null_input, 5);
    /* Possible weaknesses found:
     *  Condition 'result5==NULL' is always true
     *  Condition 'result5==NULL' is always true [knownConditionTrueFalse]
     */
    if (result5 == NULL) {
        printf("NULL input handled\n");
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['Dart', '368', 'is', '100', '181', 'Super', '18'], got <no output>
  *  test case 2 failed: expected ['Flutter', '484', 'is', '77', '129', 'Magnificent', '45'], got <no output>
  *  test case 0 failed: expected ['MSM', '240', 'is', '104', '129', 'best', '10'], got <no output>
  */

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }
    
    size_t input_len = strlen(input);
    size_t result_capacity = input_len * 2 + 1;
    char* result = (char*)malloc(result_capacity);
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
            
            char* num_str = (char*)malloc(num_len + 1);
            if (num_str == NULL) {
                free(result);
                return NULL;
            }
            
            memcpy(num_str, input + num_start, num_len);
            num_str[num_len] = '\0';
            
            long long num_val = strtoll(num_str, NULL, 10);
            free(num_str);
            
            long long new_val = num_val + k;
            
            char new_num_str[32];
            int written = snprintf(new_num_str, sizeof(new_num_str), "%lld", new_val);
            if (written < 0 || (size_t)written >= sizeof(new_num_str)) {
                free(result);
                return NULL;
            }
            
            size_t new_num_len = (size_t)written;
            size_t required_size = dst_idx + new_num_len + 1;
            
            if (required_size > result_capacity) {
                size_t new_capacity = result_capacity;
                while (new_capacity < required_size) {
                    new_capacity *= 2;
                }
                char* temp = (char*)realloc(result, new_capacity);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                result_capacity = new_capacity;
            }
            
            memcpy(result + dst_idx, new_num_str, new_num_len);
            dst_idx += new_num_len;
        } else {
            if (dst_idx + 1 >= result_capacity) {
                result_capacity *= 2;
                char* temp = (char*)realloc(result, result_capacity);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
            }
            result[dst_idx++] = input[src_idx++];
        }
    }
    
    result[dst_idx] = '\0';
    
    char* final_result = (char*)realloc(result, dst_idx + 1);
    if (final_result == NULL) {
        free(result);
        return NULL;
    }
    
    return final_result;
}

int main(void) {
    const char* test1 = "MSM240is104129best10";
    char* result1 = increment_numeric_values(test1, 0);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }
    
    const char* test2 = "Dart368is100181Super18";
    char* result2 = increment_numeric_values(test2, 0);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }
    
    const char* test3 = "Flutter484is77129Magnificent45";
    char* result3 = increment_numeric_values(test3, 0);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }
    
    const char* null_input = NULL;
    /* Possible weaknesses found:
     *  Calling function 'increment_numeric_values' returns 0
     *  Assignment 'result4=increment_numeric_values(null_input,5)', assigned value is 0
     */
    char* result4 = increment_numeric_values(null_input, 5);
    /* Possible weaknesses found:
     *  Condition 'result4==NULL' is always true
     *  Condition 'result4==NULL' is always true [knownConditionTrueFalse]
     */
    if (result4 == NULL) {
        printf("NULL input handled\n");
    } else {
        free(result4);
    }
    
    return 0;
}
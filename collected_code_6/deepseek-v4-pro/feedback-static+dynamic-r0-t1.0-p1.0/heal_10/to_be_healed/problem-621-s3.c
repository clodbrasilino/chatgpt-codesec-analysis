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
    size_t result_size = input_len + 1;
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
            int printed = snprintf(new_num_str, sizeof(new_num_str), "%lld", new_val);
            if (printed < 0 || (size_t)printed >= sizeof(new_num_str)) {
                free(result);
                return NULL;
            }
            
            size_t new_num_len = strlen(new_num_str);
            size_t remaining = input_len - src_idx;
            size_t needed_size = dst_idx + new_num_len + remaining + 1;
            
            if (needed_size > result_size) {
                char* temp = (char*)realloc(result, needed_size);
                if (temp == NULL) {
                    free(result);
                    return NULL;
                }
                result = temp;
                result_size = needed_size;
            }
            
            memcpy(result + dst_idx, new_num_str, new_num_len);
            dst_idx += new_num_len;
        } else {
            if (dst_idx + 2 > result_size) {
                size_t new_size = result_size * 2;
                if (new_size < dst_idx + 2) {
                    new_size = dst_idx + 2;
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
        size_t new_size = result_size + 1;
        char* temp = (char*)realloc(result, new_size);
        if (temp == NULL) {
            free(result);
            return NULL;
        }
        result = temp;
    }
    
    result[dst_idx] = '\0';
    
    return result;
}

int main(void) {
    const char* test1 = "MSM 240 is 104 129 best 10";
    char* result1 = increment_numeric_values(test1, 0);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }
    
    const char* test2 = "Flutter 484 is 77 129 Magnificent 45";
    char* result2 = increment_numeric_values(test2, 0);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }
    
    const char* test3 = "Dart 368 is 100 181 Super 18";
    char* result3 = increment_numeric_values(test3, 0);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }
    
    const char* test4 = "abc123def456";
    char* result4 = increment_numeric_values(test4, 5);
    if (result4 != NULL) {
        printf("%s\n", result4);
        free(result4);
    }
    
    const char* test5 = "1a2b3c";
    char* result5 = increment_numeric_values(test5, 10);
    if (result5 != NULL) {
        printf("%s\n", result5);
        free(result5);
    }
    
    const char* test6 = "no numbers here";
    char* result6 = increment_numeric_values(test6, 100);
    if (result6 != NULL) {
        printf("%s\n", result6);
        free(result6);
    }
    
    const char* test7 = "123";
    char* result7 = increment_numeric_values(test7, 0);
    if (result7 != NULL) {
        printf("%s\n", result7);
        free(result7);
    }
    
    const char* test8 = NULL;
    /* Possible weaknesses found:
     *  Calling function 'increment_numeric_values' returns 0
     *  Assignment 'result8=increment_numeric_values(test8,5)', assigned value is 0
     */
    char* result8 = increment_numeric_values(test8, 5);
    /* Possible weaknesses found:
     *  Condition 'result8==NULL' is always true
     *  Condition 'result8==NULL' is always true [knownConditionTrueFalse]
     */
    if (result8 == NULL) {
        printf("NULL input handled\n");
    } else {
        free(result8);
    }
    
    return 0;
}
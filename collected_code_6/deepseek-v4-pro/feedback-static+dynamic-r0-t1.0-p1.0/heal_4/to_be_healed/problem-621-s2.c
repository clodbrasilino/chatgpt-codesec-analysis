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
    size_t max_result_size = input_len * 20 + 1;
    char* result = (char*)malloc(max_result_size);
    if (result == NULL) {
        return NULL;
    }
    
    size_t result_pos = 0;
    size_t i = 0;
    
    while (i < input_len) {
        if (isdigit((unsigned char)input[i])) {
            size_t start = i;
            while (i < input_len && isdigit((unsigned char)input[i])) {
                i++;
            }
            
            size_t num_len = i - start;
            char* num_str = (char*)malloc(num_len + 1);
            if (num_str == NULL) {
                free(result);
                return NULL;
            }
            
            strncpy(num_str, input + start, num_len);
            num_str[num_len] = '\0';
            
            long long num = atoll(num_str);
            free(num_str);
            
            long long new_num = num + k;
            
            char new_num_str[64];
            snprintf(new_num_str, sizeof(new_num_str), "%lld", new_num);
            
            size_t new_num_len = strlen(new_num_str);
            if (result_pos + new_num_len >= max_result_size) {
                free(result);
                return NULL;
            }
            
            strcpy(result + result_pos, new_num_str);
            result_pos += new_num_len;
        } else {
            if (result_pos >= max_result_size - 1) {
                free(result);
                return NULL;
            }
            result[result_pos++] = input[i++];
        }
    }
    
    result[result_pos] = '\0';
    return result;
}

int main() {
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
    if (result1 != NULL) {
        printf("Result (+5): %s\n\n", result1);
        free(result1);
    } else {
        printf("Result (+5): (null)\n\n");
    }
    
    printf("Original: %s\n", test2);
    if (result2 != NULL) {
        printf("Result (-2): %s\n\n", result2);
        free(result2);
    } else {
        printf("Result (-2): (null)\n\n");
    }
    
    printf("Original: %s\n", test3);
    if (result3 != NULL) {
        printf("Result (+10): %s\n\n", result3);
        free(result3);
    } else {
        printf("Result (+10): (null)\n\n");
    }
    
    printf("Original: %s\n", test4);
    if (result4 != NULL) {
        printf("Result (+1): %s\n\n", result4);
        free(result4);
    } else {
        printf("Result (+1): (null)\n\n");
    }
    
    printf("Original: '%s'\n", test5);
    if (result5 != NULL) {
        printf("Result (+3): '%s'\n\n", result5);
        free(result5);
    } else {
        printf("Result (+3): (null)\n\n");
    }
    
    printf("Original: NULL\n");
    /* Possible weaknesses found:
     *  Condition 'result6!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'result6!=NULL' is always false
     */
    if (result6 != NULL) {
        printf("Result: %s\n", result6);
        free(result6);
    } else {
        printf("Result: (null)\n");
    }
    
    return 0;
}
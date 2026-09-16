#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* increment_numeric_values(const char* input, int k) {
    if (input == NULL) {
        return NULL;
    }
    
    size_t input_len = strlen(input);
    char* result = (char*)malloc(input_len * 20 + 1);
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
            strcpy(result + result_pos, new_num_str);
            result_pos += new_num_len;
        } else {
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
    char* result6 = increment_numeric_values(NULL, 5);
    
    printf("Original: %s\n", test1);
    printf("Result (+5): %s\n\n", result1);
    
    printf("Original: %s\n", test2);
    printf("Result (-2): %s\n\n", result2);
    
    printf("Original: %s\n", test3);
    printf("Result (+10): %s\n\n", result3);
    
    printf("Original: %s\n", test4);
    printf("Result (+1): %s\n\n", result4);
    
    printf("Original: '%s'\n", test5);
    printf("Result (+3): '%s'\n\n", result5);
    
    printf("Original: NULL\n");
    printf("Result: %s\n", result6);
    
    free(result1);
    free(result2);
    free(result3);
    free(result4);
    free(result5);
    
    return 0;
}
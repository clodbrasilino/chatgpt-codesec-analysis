#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char* add_spaces_before_capitals(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, 4096);
    if (input_len == 0 || input_len == 4096) {
        char* result = (char*)malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    size_t capital_count = 0;
    for (size_t i = 1; i < input_len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            capital_count++;
        }
    }

    size_t max_result_len = input_len + capital_count + 1;
    char* result = (char*)malloc(max_result_len);
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    result[result_index++] = input[0];

    for (size_t i = 1; i < input_len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            result[result_index++] = ' ';
        }
        result[result_index++] = input[i];
    }

    result[result_index] = '\0';
    return result;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsATest";
    char* result = add_spaces_before_capitals(test_str);
    
    if (result != NULL) {
        printf("Input: %s\n", test_str);
        printf("Output: %s\n", result);
        free(result);
    } else {
        printf("Error processing string\n");
    }
    
    return 0;
}
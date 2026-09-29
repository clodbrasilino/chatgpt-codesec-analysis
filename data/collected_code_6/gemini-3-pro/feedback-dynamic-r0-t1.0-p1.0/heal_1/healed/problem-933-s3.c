#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* camel_to_snake(const char *input) {
    if (!input) return NULL;
    
    size_t len = strlen(input);
    char *result = (char*)malloc(len * 2 + 1);
    if (!result) return NULL;
    
    int j = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (i > 0 && islower((unsigned char)input[i-1]) && isupper((unsigned char)input[i])) {
            result[j++] = '_';
        }
        result[j++] = tolower((unsigned char)input[i]);
    }
    result[j] = '\0';
    
    char *final_result = (char*)realloc(result, j + 1);
    if (!final_result) {
        return result; 
    }
    
    return final_result;
}

int main(void) {
    const char *test_str = "camelCaseStringExample";
    char *snake_str = camel_to_snake(test_str);
    
    if (snake_str) {
        printf("%s\n", snake_str);
        free(snake_str);
    }
    
    return 0;
}
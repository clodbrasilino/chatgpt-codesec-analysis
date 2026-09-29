#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char* camel_to_snake(const char *input) {
    if (!input) {
        return NULL;
    }

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    char *result = (char*)malloc(len * 2 + 1);
    if (!result) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (i > 0 && islower((unsigned char)input[i - 1]) && isupper((unsigned char)input[i])) {
            result[j++] = '_';
            result[j++] = tolower((unsigned char)input[i]);
        } else {
            result[j++] = input[i];
        }
    }
    result[j] = '\0';

    char *final_result = (char*)realloc(result, j + 1);
    return final_result ? final_result : result;
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
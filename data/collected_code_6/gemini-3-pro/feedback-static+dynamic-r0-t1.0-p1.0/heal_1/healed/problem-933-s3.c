#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* camel_to_snake(const char *input) {
    if (!input) return NULL;

    size_t in_len = strlen(input);
    size_t out_size = in_len * 2 + 1;
    char *result = (char*)malloc(out_size);
    if (!result) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < in_len; i++) {
        char c = input[i];
        if (isupper((unsigned char)c)) {
            if (i > 0) {
                result[j++] = '_';
            }
            result[j++] = tolower((unsigned char)c);
        } else {
            result[j++] = c;
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
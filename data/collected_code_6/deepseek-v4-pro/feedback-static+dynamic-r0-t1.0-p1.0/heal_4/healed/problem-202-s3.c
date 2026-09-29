#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char *remove_even_chars(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    const char *p = str;
    while (*p != '\0') {
        len++;
        if (len > SIZE_MAX / 2) {
            return NULL;
        }
        p++;
    }
    
    size_t new_len = (len + 1) / 2;
    
    char *result = (char *)malloc(new_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i += 2) {
        result[j++] = str[i];
    }
    result[j] = '\0';
    
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "abcdefgh",
        "a",
        "",
        "abc",
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        char *result = remove_even_chars(test_cases[i]);
        if (result != NULL) {
            printf("Input: \"%s\" -> Output: \"%s\"\n", test_cases[i], result);
            free(result);
        }
    }
    
    const char *null_input = NULL;
    char *null_result = remove_even_chars(null_input);
    if (null_result == NULL) {
        printf("NULL input -> NULL output\n");
    }
    
    return 0;
}
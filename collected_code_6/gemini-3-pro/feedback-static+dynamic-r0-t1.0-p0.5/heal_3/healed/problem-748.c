#include <stdio.h>
#include <stdlib.h>

char* add_spaces(const char* input) {
    if (!input) return NULL;

    size_t len = 0;
    while (input[len] != '\0') {
        len++;
    }

    size_t max_len = len * 2 + 1;
    char* result = (char*)malloc(max_len);
    if (!result) return NULL;

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        result[j++] = input[i];
        if (input[i] >= 'a' && input[i] <= 'z' && 
            input[i+1] >= 'A' && input[i+1] <= 'Z') {
            result[j++] = ' ';
        }
    }
    result[j] = '\0';

    return result;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsACProgram";
    char* spaced_str = add_spaces(test_str);
    
    if (spaced_str) {
        printf("Original: %s\n", test_str);
        printf("Spaced: %s\n", spaced_str);
        free(spaced_str);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }

    return 0;
}
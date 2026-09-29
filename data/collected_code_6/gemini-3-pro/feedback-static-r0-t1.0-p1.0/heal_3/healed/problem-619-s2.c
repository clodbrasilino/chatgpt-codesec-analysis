#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 4096

char* move_numbers(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strlen(input);
    if (len > MAX_INPUT_LEN) {
        len = MAX_INPUT_LEN;
    }

    char* result = (char*)malloc(len + 1);
    
    if (result == NULL) {
        return NULL;
    }

    size_t result_idx = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            result[result_idx++] = input[i];
        }
    }

    for (size_t i = 0; i < len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            result[result_idx++] = input[i];
        }
    }

    result[result_idx] = '\0';

    return result;
}

int main(void) {
    const char* str = "a1b2c3d4e5";
    
    char* modified_str = move_numbers(str);
    
    if (modified_str != NULL) {
        printf("Original: %s\n", str);
        printf("Modified: %s\n", modified_str);
        free(modified_str);
    } else {
        printf("Memory allocation failed or invalid input.\n");
    }

    return 0;
}
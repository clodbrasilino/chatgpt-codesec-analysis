#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* move_numbers(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
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

int main() {
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
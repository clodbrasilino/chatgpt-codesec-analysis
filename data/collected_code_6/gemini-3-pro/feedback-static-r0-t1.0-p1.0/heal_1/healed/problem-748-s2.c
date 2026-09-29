#include <stdio.h>
#include <stdlib.h>

char* add_spaces(const char* input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = 0;
    size_t spaces_needed = 0;

    while (input[len] != '\0') {
        if (input[len] >= 'a' && input[len] <= 'z' && 
            input[len + 1] >= 'A' && input[len + 1] <= 'Z') {
            spaces_needed++;
        }
        len++;
    }

    char* output = malloc(len + spaces_needed + 1);
    if (output == NULL) {
        return NULL;
    }

    size_t i = 0;
    size_t j = 0;
    
    while (i < len) {
        output[j++] = input[i];
        if (input[i] >= 'a' && input[i] <= 'z' && 
            input[i + 1] >= 'A' && input[i + 1] <= 'Z') {
            output[j++] = ' ';
        }
        i++;
    }
    output[j] = '\0';

    return output;
}

int main(void) {
    const char* test_str = "HelloWorldThisIsCTesting";
    char* result = add_spaces(test_str);

    if (result != NULL) {
        printf("Original: %s\n", test_str);
        printf("Modified: %s\n", result);
        free(result);
    } else {
        fprintf(stderr, "Error processing string.\n");
        return 1;
    }

    return 0;
}
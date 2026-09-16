#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replace_spaces(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t space_count = 0;
    size_t length = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            space_count++;
        }
        length++;
    }

    size_t new_length = length + (space_count * 2);
    char* new_str = (char*)malloc(new_length + 1);

    if (new_str == NULL) {
        return NULL;
    }

    size_t j = 0;
    for (size_t i = 0; i < length; i++) {
        if (str[i] == ' ') {
            new_str[j++] = '%';
            new_str[j++] = '2';
            new_str[j++] = '0';
        } else {
            new_str[j++] = str[i];
        }
    }
    
    new_str[new_length] = '\0';

    return new_str;
}

int main(void) {
    const char* input_string = "replace all spaces in the given string";
    
    char* result = replace_spaces(input_string);
    
    if (result != NULL) {
        printf("%s\n", result);
        free(result);
        result = NULL;
    } else {
        fprintf(stderr, "Memory allocation failed or input was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
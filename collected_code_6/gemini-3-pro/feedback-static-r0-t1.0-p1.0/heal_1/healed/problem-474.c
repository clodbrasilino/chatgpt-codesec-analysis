#include <stdio.h>
#include <stdlib.h>

char* replace_character(const char* str, char old_char, char new_char) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    
    char* new_str = (char*)malloc(len + 1);
    if (new_str == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] == old_char) {
            new_str[i] = new_char;
        } else {
            new_str[i] = str[i];
        }
    }
    new_str[len] = '\0';

    return new_str;
}

int main(void) {
    const char* original_string = "hello world";
    char old_c = 'o';
    char new_c = 'a';

    char* result = replace_character(original_string, old_c, new_c);
    
    if (result != NULL) {
        printf("Original: %s\n", original_string);
        printf("Modified: %s\n", result);
        free(result);
    } else {
        printf("Memory allocation failed or input was NULL.\n");
    }

    return 0;
}
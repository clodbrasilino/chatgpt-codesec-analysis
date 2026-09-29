#include <stdio.h>
#include <stdlib.h>

char* replace_char(const char* str, char find, char replace) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Assignment 'max_len=8192', assigned value is 8192
     */
    size_t max_len = 8192; 

    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Either the condition 'len<max_len' is redundant or the array 'str[14]' is accessed at index 8191, which is out of bounds. [arrayIndexOutOfBoundsCond]
     *  Assuming that condition 'len<max_len' is not redundant
     */
    while (len < max_len && str[len] != '\0') {
        len++;
    }

    char* result = (char*)malloc(len + 1);

    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        if (str[i] == find) {
            result[i] = replace;
        } else {
            result[i] = str[i];
        }
    }
    result[len] = '\0';

    return result;
}

int main(void) {
    const char* original_string = "Hello, World!";
    char find_char = 'o';
    char replace_char_val = 'X';

    char* new_string = replace_char(original_string, find_char, replace_char_val);

    if (new_string != NULL) {
        printf("Original: %s\n", original_string);
        printf("Modified: %s\n", new_string);
        free(new_string);
    } else {
        printf("Memory allocation failed or input string was NULL.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
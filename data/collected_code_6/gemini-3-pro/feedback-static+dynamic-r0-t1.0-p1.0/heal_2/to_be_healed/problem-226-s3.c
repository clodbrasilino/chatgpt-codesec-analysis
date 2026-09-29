#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

char* remove_odd_indices(const char* str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index out of bounds
     *  Assuming that condition 'len<4096' is not redundant
     *  Either the condition 'len<4096' is redundant or the array 'str[11]' is accessed at index 4095, which is out of bounds. [arrayIndexOutOfBoundsCond]
     */
    while (len < MAX_STR_LEN && str[len] != '\0') {
        len++;
    }

    size_t new_len = (len / 2) + (len % 2);

    char* result = (char*)malloc(new_len + 1);
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
    const char* original_string = "HelloWorld";
    char* modified_string = remove_odd_indices(original_string);

    if (modified_string != NULL) {
        printf("Original: %s\n", original_string);
        printf("Modified: %s\n", modified_string);
        free(modified_string);
    } else {
        printf("Memory allocation failed or input was NULL.\n");
    }

    return 0;
}
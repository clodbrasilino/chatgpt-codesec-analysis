#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

char* extract_rear_elements(const char** strings, size_t num_strings) {
    if (strings == NULL || num_strings == 0) {
        return NULL;
    }

    char* result = (char*)malloc((num_strings + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num_strings; ++i) {
        if (strings[i] == NULL || strings[i][0] == '\0') {
            free(result);
            return NULL;
        }
        
        size_t len = 0;
        while (len < MAX_STR_LEN && strings[i][len] != '\0') {
            len++;
        }
        
        result[i] = strings[i][len - 1];
    }
    
    result[num_strings] = '\0';
    return result;
}

int main(void) {
    const char* str_array[] = {"apple", "banana", "cherry", "date"};
    size_t num_strings = sizeof(str_array) / sizeof(str_array[0]);

    char* rear_elements = extract_rear_elements(str_array, num_strings);
    
    if (rear_elements != NULL) {
        printf("Rear elements: %s\n", rear_elements);
        free(rear_elements);
    } else {
        printf("Failed to extract rear elements or invalid input.\n");
    }

    return 0;
}
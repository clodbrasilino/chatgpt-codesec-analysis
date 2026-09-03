#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_elements(const char *array[], size_t count) {
    if (count == 0) return NULL;
    
    size_t total_length = 0;
    for (size_t i = 0; i < count; ++i) {
        total_length += strlen(array[i]);
        if (i < count - 1) total_length++; // Add space between elements
    }
    
    char *result = (char *)malloc(total_length + 1);
    if (result == NULL) return NULL;
    
    result[0] = '\0';
    for (size_t i = 0; i < count; ++i) {
        strcat(result, array[i]);
        if (i < count - 1 && array[i+1][0] != ' ') strcat(result, " "); // Add space if the next element doesn't start with a space
    }
    
    return result;
}

int main() {
    const char *elements[] = {"Hi there", "How are you"};
    size_t count = sizeof(elements) / sizeof(elements[0]);
    
    char *combined = concat_elements(elements, count);
    if (combined != NULL) {
        printf("%s\n", combined);
        free(combined);
    }

    const char *elements2[] = {"Part of the journey is end"};
    count = sizeof(elements2) / sizeof(elements2[0]);
    
    combined = concat_elements(elements2, count);
    if (combined != NULL) {
        printf("%s\n", combined);
        free(combined);
    }

    const char *elements3[] = {"hello there", "have a rocky day"};
    count = sizeof(elements3) / sizeof(elements3[0]);
    
    combined = concat_elements(elements3, count);
    if (combined != NULL) {
        printf("%s\n", combined);
        free(combained);
    }
    
    return 0;
}
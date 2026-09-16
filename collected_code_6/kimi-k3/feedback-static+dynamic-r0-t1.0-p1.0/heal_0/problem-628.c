#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* replaceSpaces(const char* str) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = strlen(str);
    size_t spaceCount = 0;
    
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            spaceCount++;
        }
    }
    
    if (len > (SIZE_MAX - 1) / 3 && spaceCount > 0) {
        return NULL;
    }
    
    size_t newLen = len + (spaceCount * 2) + 1;
    char* result = malloc(newLen);
    
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == ' ') {
            result[j++] = '%';
            result[j++] = '2';
            result[j++] = '0';
        } else {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    
    return result;
}

int main(void) {
    const char* testString = "Hello World This Is A Test";
    char* modifiedString = replaceSpaces(testString);
    
    if (modifiedString != NULL) {
        printf("Original: %s\n", testString);
        printf("Modified: %s\n", modifiedString);
        free(modifiedString);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
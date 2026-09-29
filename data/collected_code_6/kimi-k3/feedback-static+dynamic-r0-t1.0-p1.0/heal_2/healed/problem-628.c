#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char* replaceSpaces(const char* str, size_t maxLen) {
    if (str == NULL) {
        return NULL;
    }
    
    size_t len = 0;
    size_t spaceCount = 0;
    int terminated = 0;
    
    for (size_t i = 0; i < maxLen; i++) {
        if (str[i] == '\0') {
            terminated = 1;
            break;
        }
        len++;
        if (str[i] == ' ') {
            spaceCount++;
        }
    }
    
    if (!terminated) {
        return NULL;
    }
    
    if (spaceCount > 0 && len > (SIZE_MAX - 1 - (spaceCount * 2))) {
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
    size_t testLen = 0;
    
    while (testString[testLen] != '\0') {
        testLen++;
    }
    
    char* modifiedString = replaceSpaces(testString, testLen + 1);
    
    if (modifiedString != NULL) {
        printf("Original: %s\n", testString);
        printf("Modified: %s\n", modifiedString);
        free(modifiedString);
    } else {
        fprintf(stderr, "Memory allocation failed or invalid input\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
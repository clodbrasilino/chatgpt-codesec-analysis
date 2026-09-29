#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

char findMaxOccurringChar(const char *str, int *maxCount) {
    int freq[256] = {0};
    size_t i;
    int max = 0;
    char result = '\0';
    
    if (str == NULL || maxCount == NULL) {
        if (maxCount != NULL) {
            *maxCount = 0;
        }
        return '\0';
    }
    
    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        freq[c]++;
    }
    
    for (i = 0; i < 256; i++) {
        if (freq[i] > max) {
            max = freq[i];
            result = (char)i;
        }
    }
    
    *maxCount = max;
    return result;
}

int main(void) {
    char *buffer = NULL;
    size_t bufferSize = 0;
    ssize_t bytesRead;
    int maxCount = 0;
    char maxChar;
    size_t len;
    
    printf("Enter a string: ");
    
    bytesRead = getline(&buffer, &bufferSize, stdin);
    
    if (bytesRead == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }
    
    len = strcspn(buffer, "\n");
    buffer[len] = '\0';
    
    if (len == 0) {
        printf("Empty string provided\n");
        free(buffer);
        return 0;
    }
    
    maxChar = findMaxOccurringChar(buffer, &maxCount);
    
    if (maxCount > 0) {
        printf("Maximum occurring character: '%c' (appears %d times)\n", maxChar, maxCount);
    } else {
        printf("No characters found\n");
    }
    
    free(buffer);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* minimizeString(const char* str, size_t len) {
    if (str == NULL) {
        return NULL;
    }
    
    if (len == 0) {
        char* result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }
    
    int freq[256] = {0};
    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)str[i]]++;
    }
    
    int maxFreq = 0;
    int maxChar = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            maxChar = i;
        }
    }
    
    size_t newLen = len - (size_t)maxFreq;
    char* result = malloc(newLen + 1);
    if (result == NULL) {
        return NULL;
    }
    
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if ((unsigned char)str[i] != maxChar) {
            result[j++] = str[i];
        }
    }
    result[j] = '\0';
    
    return result;
}

int main(void) {
    char* input = NULL;
    size_t inputSize = 0;
    ssize_t bytesRead;
    
    bytesRead = getline(&input, &inputSize, stdin);
    if (bytesRead != -1) {
        size_t len = (size_t)bytesRead;
        
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
            len--;
        }
        
        char* result = minimizeString(input, len);
        if (result != NULL) {
            printf("%s\n", result);
            free(result);
        }
        
        free(input);
    }
    
    return 0;
}
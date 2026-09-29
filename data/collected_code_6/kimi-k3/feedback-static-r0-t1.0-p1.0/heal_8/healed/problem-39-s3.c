#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 1024

bool canRearrange(const char *str, size_t len) {
    if (str == NULL) {
        return false;
    }
    
    if (len <= 1) {
        return true;
    }
    
    int freq[256] = {0};
    int max_freq = 0;
    
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        freq[c]++;
        if (freq[c] > max_freq) {
            max_freq = freq[c];
        }
    }
    
    return max_freq <= (int)((len + 1) / 2);
}

size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int main(void) {
    char *buffer = malloc(BUFFER_SIZE + 1);
    if (buffer == NULL) {
        return EXIT_FAILURE;
    }
    
    if (fgets(buffer, BUFFER_SIZE + 1, stdin) == NULL) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    size_t len = safe_strlen(buffer, BUFFER_SIZE + 1);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (canRearrange(buffer, len)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    free(buffer);
    return EXIT_SUCCESS;
}
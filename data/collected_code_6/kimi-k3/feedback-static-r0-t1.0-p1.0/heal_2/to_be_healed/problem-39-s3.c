#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    size_t len = safe_strlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    if (canRearrange(buffer, len)) {
        printf("true\n");
    } else {
        printf("false\n");
    }
    
    return EXIT_SUCCESS;
}
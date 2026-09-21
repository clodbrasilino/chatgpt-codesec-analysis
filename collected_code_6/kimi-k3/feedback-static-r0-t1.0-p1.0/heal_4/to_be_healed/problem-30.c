#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

long long countSubstrings(const char *s, size_t len) {
    if (s == NULL) {
        return 0;
    }
    
    int freq[256] = {0};
    
    for (size_t i = 0; i < len; i++) {
        freq[(unsigned char)s[i]]++;
    }
    
    long long count = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            count += (long long)freq[i] * (freq[i] + 1) / 2;
        }
    }
    
    return count;
}

int main(void) {
    size_t capacity = 1024;
    size_t len = 0;
    char *buffer = malloc(capacity);
    
    if (buffer == NULL) {
        return 1;
    }
    
    int c;
    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = getchar()) != EOF && c != '\n') {
        if (len + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 1;
            }
            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 1;
            }
            buffer = new_buffer;
            capacity = new_capacity;
        }
        buffer[len++] = (char)c;
    }
    
    if (ferror(stdin)) {
        free(buffer);
        return 1;
    }
    
    buffer[len] = '\0';
    
    long long result = countSubstrings(buffer, len);
    printf("%lld\n", result);
    
    free(buffer);
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>

unsigned long long countNonEmptySubstrings(const char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
        return 0;
    }
    
    size_t len = strnlen(str, max_len);
    if (len == 0) {
        return 0;
    }
    
    if (len > UINT64_MAX / (len + 1)) {
        return 0;
    }
    
    return (unsigned long long)len * (len + 1) / 2;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t bytes_read;
    
    printf("Enter a string: ");
    
    errno = 0;
    bytes_read = getline(&buffer, &buffer_size, stdin);
    
    if (bytes_read == -1) {
        if (errno != 0) {
            perror("Error reading input");
        } else {
            fprintf(stderr, "Error reading input\n");
        }
        free(buffer);
        return 1;
    }
    
    if (bytes_read > 0 && buffer[bytes_read - 1] == '\n') {
        buffer[bytes_read - 1] = '\0';
        bytes_read--;
    }
    
    unsigned long long result = countNonEmptySubstrings(buffer, (size_t)bytes_read);
    printf("Number of non-empty substrings: %llu\n", result);
    
    free(buffer);
    return 0;
}
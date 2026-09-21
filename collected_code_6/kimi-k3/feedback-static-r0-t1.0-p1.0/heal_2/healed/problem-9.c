#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

int findMinRotations(const char *str, size_t len) {
    if (str == NULL) {
        return -1;
    }
    
    if (len == 0) {
        return 0;
    }
    
    if (len > (SIZE_MAX - 1) / 2 || len > INT_MAX) {
        return -1;
    }
    
    size_t doubled_len = 2 * len;
    char *doubled = (char *)malloc(doubled_len + 1);
    if (doubled == NULL) {
        return -1;
    }
    
    if (len > 0) {
        memcpy(doubled, str, len);
        memcpy(doubled + len, str, len);
    }
    doubled[doubled_len] = '\0';
    
    int result = -1;
    for (size_t i = 1; i <= len; i++) {
        if (strncmp(doubled + i, str, len) == 0) {
            if (i == len) {
                result = (int)len;
            } else {
                result = (int)i;
            }
            break;
        }
    }
    
    free(doubled);
    doubled = NULL;
    
    return result;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t len;
    
    len = getline(&buffer, &buffer_size, stdin);
    if (len == -1) {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    int rotations = findMinRotations(buffer, (size_t)len);
    if (rotations >= 0) {
        printf("%d\n", rotations);
    } else {
        free(buffer);
        return EXIT_FAILURE;
    }
    
    free(buffer);
    return EXIT_SUCCESS;
}
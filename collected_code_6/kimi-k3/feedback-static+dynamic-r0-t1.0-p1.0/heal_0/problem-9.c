#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int findMinRotations(const char *str) {
    if (str == NULL) {
        return -1;
    }
    
    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }
    
    if (len > (SIZE_MAX - 1) / 2) {
        return -1;
    }
    
    size_t doubled_len = 2 * len;
    char *doubled = (char *)malloc(doubled_len + 1);
    if (doubled == NULL) {
        return -1;
    }
    
    memcpy(doubled, str, len);
    memcpy(doubled + len, str, len);
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
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
    
    int rotations = findMinRotations(buffer);
    if (rotations >= 0) {
        printf("%d\n", rotations);
    } else {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
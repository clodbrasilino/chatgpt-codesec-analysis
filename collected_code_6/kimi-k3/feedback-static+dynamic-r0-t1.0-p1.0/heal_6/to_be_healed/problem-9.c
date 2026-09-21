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
    
    if (len > (SIZE_MAX - 1) / 2) {
        return -1;
    }
    
    size_t doubled_len = 2 * len;
    char *doubled = (char *)malloc(doubled_len + 1);
    if (doubled == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled, str, len);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    
    size_t len = strnlen(buffer, sizeof(buffer));
    if (len == sizeof(buffer)) {
        return EXIT_FAILURE;
    }
    
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }
    
    int rotations = findMinRotations(buffer, len);
    if (rotations >= 0) {
        printf("%d\n", rotations);
    } else {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
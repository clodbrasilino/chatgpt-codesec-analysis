#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_rotations_same_string(const char *str) {
    size_t len = strnlen(str, 4096);
    if (len == 0) {
        return 0;
    }
    
    size_t doubled_size = 2 * len + 1;
    
    char *doubled = (char *)malloc(doubled_size);
    if (doubled == NULL) {
        exit(EXIT_FAILURE);
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled, str, len);
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled + len, str, len);
    doubled[2 * len] = '\0';
    
    for (size_t i = 1; i <= len; i++) {
        if (memcmp(str, doubled + i, len) == 0) {
            free(doubled);
            return (int)i;
        }
    }
    
    free(doubled);
    return (int)len;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abab";
    const char *test3 = "abcab";
    const char *test4 = "abc";
    const char *test5 = "";
    
    printf("%d\n", min_rotations_same_string(test1));
    printf("%d\n", min_rotations_same_string(test2));
    printf("%d\n", min_rotations_same_string(test3));
    printf("%d\n", min_rotations_same_string(test4));
    printf("%d\n", min_rotations_same_string(test5));
    
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int min_rotations_same_string(const char *str) {
    if (str == NULL) return -1;
    
    size_t len = strnlen(str, 1024);
    if (len == 0) return 0;
    
    if (len > (SIZE_MAX - 1) / 2) return -1;
    
    size_t doubled_size = 2 * len + 1;
    
    char *doubled = (char *)malloc(doubled_size);
    if (doubled == NULL) return -1;
    
    /* Possible weaknesses found:
     *  First condition
     */
    if (doubled_size <= len) {
        free(doubled);
        return -1;
    }
    
    /* Possible weaknesses found:
     *  The if condition is the same as the previous if condition [duplicateCondition]
     *  Second condition
     */
    if (len >= doubled_size) {
        free(doubled);
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled, str, len);
    doubled[len] = '\0';
    
    size_t first_len = strnlen(doubled, doubled_size);
    
    if (first_len < doubled_size) {
        size_t remaining = doubled_size - first_len;
        size_t copy_len = len;
        
        if (copy_len > remaining - 1) {
            copy_len = remaining - 1;
        }
        
        if (first_len + copy_len >= doubled_size) {
            free(doubled);
            return -1;
        }
        
        if (first_len + copy_len > doubled_size - 1) {
            free(doubled);
            return -1;
        }
        
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(doubled + first_len, str, copy_len);
        doubled[first_len + copy_len] = '\0';
    }
    
    int result = -1;
    
    for (size_t i = 1; i <= len; i++) {
        if (i + len <= doubled_size) {
            if (memcmp(doubled + i, str, len) == 0) {
                result = (int)i;
                break;
            }
        }
    }
    
    free(doubled);
    return result;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abab";
    const char *test3 = "abcde";
    const char *test4 = "";
    const char *test5 = "a";
    
    printf("%d\n", min_rotations_same_string(test1));
    printf("%d\n", min_rotations_same_string(test2));
    printf("%d\n", min_rotations_same_string(test3));
    printf("%d\n", min_rotations_same_string(test4));
    printf("%d\n", min_rotations_same_string(test5));
    
    return 0;
}
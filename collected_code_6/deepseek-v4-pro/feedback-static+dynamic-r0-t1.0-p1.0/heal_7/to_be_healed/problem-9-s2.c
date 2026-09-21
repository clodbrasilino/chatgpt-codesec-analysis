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
    
    if (doubled_size < len + 1) {
        free(doubled);
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(doubled, str, len);
    doubled[len] = '\0';
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t first_len = strlen(doubled);
    size_t remaining = doubled_size - first_len;
    if (remaining > 0) {
        /* Possible weaknesses found:
         * Flawfinder strncat: Easily used incorrectly (e.g., incorrectly computing the correct maximum size to add) [MS-banned] (CWE-120). Consider strcat_s, strlcat, snprintf, or automatically resizing strings. (risk 1, buffer)
         */
        strncat(doubled, str, remaining - 1);
        doubled[doubled_size - 1] = '\0';
    }
    
    int result = -1;
    
    for (size_t i = 1; i <= len; i++) {
        if (i + len <= doubled_size && memcmp(doubled + i, str, len) == 0) {
            result = (int)i;
            break;
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
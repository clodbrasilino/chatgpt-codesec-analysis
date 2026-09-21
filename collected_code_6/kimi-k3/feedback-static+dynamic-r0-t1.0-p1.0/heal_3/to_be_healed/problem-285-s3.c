#include <stdio.h>
#include <string.h>

int match_pattern(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    
    if (len == 0) {
        return 0;
    }
    
    size_t i = 0;
    
    while (i < len) {
        if (str[i] == 'a') {
            size_t b_count = 0;
            size_t j = i + 1;
            
            while (j < len && str[j] == 'b') {
                b_count++;
                j++;
            }
            
            if (b_count >= 2 && b_count <= 3) {
                return 1;
            }
        }
        i++;
    }
    
    return 0;
}

int main(void) {
    const char *test1 = "abb";
    const char *test2 = "abbb";
    const char *test3 = "ab";
    const char *test4 = "abbbb";
    const char *test5 = "xyzabbxyz";
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("test1: %d\n", match_pattern(test1, strlen(test1)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("test2: %d\n", match_pattern(test2, strlen(test2)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("test3: %d\n", match_pattern(test3, strlen(test3)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("test4: %d\n", match_pattern(test4, strlen(test4)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("test5: %d\n", match_pattern(test5, strlen(test5)));
    
    return 0;
}
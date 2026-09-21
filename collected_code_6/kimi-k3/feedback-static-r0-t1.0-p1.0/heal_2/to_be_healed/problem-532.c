#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_permutation(const char *str1, size_t len1, const char *str2, size_t len2) {
    if (str1 == NULL || str2 == NULL) {
        return false;
    }
    
    if (len1 != len2) {
        return false;
    }
    
    if (len1 == 0) {
        return true;
    }
    
    int char_count[256] = {0};
    
    for (size_t i = 0; i < len1; i++) {
        char_count[(unsigned char)str1[i]]++;
        char_count[(unsigned char)str2[i]]--;
    }
    
    for (int i = 0; i < 256; i++) {
        if (char_count[i] != 0) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test1_str1 = "listen";
    const char *test1_str2 = "silent";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test1_len1 = strlen(test1_str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test1_len2 = strlen(test1_str2);
    
    const char *test2_str1 = "hello";
    const char *test2_str2 = "world";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test2_len1 = strlen(test2_str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test2_len2 = strlen(test2_str2);
    
    const char *test3_str1 = "aab";
    const char *test3_str2 = "aba";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test3_len1 = strlen(test3_str1);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t test3_len2 = strlen(test3_str2);
    
    printf("Test 1: \"%s\" and \"%s\" - %s\n", 
           test1_str1, test1_str2, 
           is_permutation(test1_str1, test1_len1, test1_str2, test1_len2) ? "Permutations" : "Not permutations");
    
    printf("Test 2: \"%s\" and \"%s\" - %s\n", 
           test2_str1, test2_str2, 
           is_permutation(test2_str1, test2_len1, test2_str2, test2_len2) ? "Permutations" : "Not permutations");
    
    printf("Test 3: \"%s\" and \"%s\" - %s\n", 
           test3_str1, test3_str2, 
           is_permutation(test3_str1, test3_len1, test3_str2, test3_len2) ? "Permutations" : "Not permutations");
    
    return 0;
}
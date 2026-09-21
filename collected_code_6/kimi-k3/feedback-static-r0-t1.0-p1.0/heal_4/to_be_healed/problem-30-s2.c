#include <stdio.h>
#include <string.h>

long long countSubstringsWithSameStartAndEnd(const char *str, size_t len) {
    if (str == NULL) {
        return 0;
    }
    
    long long count = 0;
    
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    
    return count;
}

int main(void) {
    const char *test1 = "abcab";
    const char *test2 = "aba";
    const char *test3 = "a";
    const char *test4 = "";
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("String: \"%s\" -> Count: %lld\n", test1, countSubstringsWithSameStartAndEnd(test1, strlen(test1)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("String: \"%s\" -> Count: %lld\n", test2, countSubstringsWithSameStartAndEnd(test2, strlen(test2)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("String: \"%s\" -> Count: %lld\n", test3, countSubstringsWithSameStartAndEnd(test3, strlen(test3)));
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    printf("String: \"%s\" -> Count: %lld\n", test4, countSubstringsWithSameStartAndEnd(test4, strlen(test4)));
    
    return 0;
}
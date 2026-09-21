#include <stdio.h>
#include <string.h>

int min_swaps_binary(const char *s1, const char *s2, size_t len) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    size_t m1 = 0;
    size_t m2 = 0;

    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1' && s2[i] == '0') {
                m1++;
            } else if (s1[i] == '0' && s2[i] == '1') {
                m2++;
            } else {
                return -1;
            }
        }
    }

    if (m1 != m2) {
        return -1;
    }

    return (int)m1;
}

int main(void) {
    const char *str1 = "1100";
    const char *str2 = "0011";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str1);
    
    int result = min_swaps_binary(str1, str2, len);
    
    printf("%d\n", result);
    
    return 0;
}
#include <stdio.h>

int min_swaps_binary(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    size_t len = 0;
    size_t m1 = 0;
    size_t m2 = 0;

    while (s1[len] != '\0' && s2[len] != '\0') {
        if (s1[len] != s2[len]) {
            if (s1[len] == '1' && s2[len] == '0') {
                m1++;
            } else if (s1[len] == '0' && s2[len] == '1') {
                m2++;
            } else {
                return -1;
            }
        }
        len++;
    }

    if (s1[len] != '\0' || s2[len] != '\0') {
        return -1;
    }

    if (m1 != m2) {
        return -1;
    }

    return (int)m1;
}

int main(void) {
    const char *str1 = "1100";
    const char *str2 = "0011";
    
    int result = min_swaps_binary(str1, str2);
    
    printf("%d\n", result);
    
    return 0;
}
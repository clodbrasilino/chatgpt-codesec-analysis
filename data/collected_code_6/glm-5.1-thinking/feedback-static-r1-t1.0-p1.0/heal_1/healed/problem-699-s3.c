#include <stdio.h>
#include <string.h>

#define MAX_LEN 4096

int min_swaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return -1;
    }

    size_t len1 = strnlen(s1, MAX_LEN);
    if (len1 == MAX_LEN) {
        return -1;
    }

    size_t len2 = strnlen(s2, MAX_LEN);
    if (len2 == MAX_LEN) {
        return -1;
    }

    if (len1 != len2) {
        return -1;
    }

    int m10 = 0;
    int m01 = 0;

    for (size_t i = 0; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') || (s2[i] != '0' && s2[i] != '1')) {
            return -1;
        }
        if (s1[i] == '1' && s2[i] == '0') {
            m10++;
        } else if (s1[i] == '0' && s2[i] == '1') {
            m01++;
        }
    }

    if (m10 != m01) {
        return -1;
    }

    return m10;
}

int main(void) {
    const char *s1 = "100110";
    const char *s2 = "011001";
    
    int result = min_swaps(s1, s2);
    
    if (result != -1) {
        printf("%d\n", result);
    }
    
    return 0;
}
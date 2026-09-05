#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    if (len1 != len2) {
        return -1;
    }
    size_t len = len1;
    size_t count_mismatch1 = 0;
    size_t count_mismatch2 = 0;
    for (size_t i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                count_mismatch1++;
            } else {
                count_mismatch2++;
            }
        }
    }
    if (count_mismatch1 != count_mismatch2) {
        return -1;
    }
    return (int)count_mismatch1;
}

int main() {
    const char *s1 = "11001";
    const char *s2 = "00111";
    int result = min_swaps(s1, s2);
    printf("%d\n", result);
    return 0;
}
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
    if ((count_mismatch1 + count_mismatch2) % 2 != 0) {
        return -1;
    }
    if (count_mismatch1 % 2 != 0) {
        return (int)((count_mismatch1 / 2) + (count_mismatch2 / 2) + 2);
    }
    return (int)((count_mismatch1 / 2) + (count_mismatch2 / 2));
}

int main() {
    char s1[100];
    char s2[100];
    while (scanf("%99s %99s", s1, s2) == 2) {
        int result = min_swaps(s1, s2);
        if (result == -1) {
            printf("Not Possible\n");
        } else {
            printf("%d\n", result);
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min_swaps(const char *s1, const char *s2, size_t max_len) {
    size_t len1 = strnlen(s1, max_len);
    size_t len2 = strnlen(s2, max_len);
    if (len1 != len2) {
        return -1;
    }
    size_t n = len1;
    int x = 0;
    int y = 0;
    for (size_t i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                x++;
            } else {
                y++;
            }
        }
    }
    if ((x + y) % 2 != 0) {
        return -1;
    }
    return (x / 2) + (y / 2) + (x % 2) * 2;
}

int main() {
    const char s1[] = "1001";
    const char s2[] = "0110";
    int result = min_swaps(s1, s2, sizeof(s1));
    printf("%d\n", result);
    return 0;
}
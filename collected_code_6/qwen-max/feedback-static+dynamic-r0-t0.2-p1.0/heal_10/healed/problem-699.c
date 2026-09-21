#include <stdio.h>
#include <string.h>

int minSwaps(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return -1;
    size_t len1 = 0;
    while (s1[len1] != '\0' && (s1[len1] == '0' || s1[len1] == '1')) len1++;
    size_t len2 = 0;
    while (s2[len2] != '\0' && (s2[len2] == '0' || s2[len2] == '1')) len2++;
    if (len1 != len2 || s1[len1] != '\0' || s2[len2] != '\0') return -1;
    int count[2] = {0, 0};
    for (size_t i = 0; i < len1; ++i) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
        }
    }
    if (count[0] == count[1]) return count[0];
    return -1;
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "1001";
    int result = minSwaps(s1, s2);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Cannot convert one string to another with swaps.\n");
    }
    return 0;
}
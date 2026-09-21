#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 2 failed: expected 3, got <no output>
  */

int minSwaps(const char *s1, const char *s2) {
    int count[2] = {0, 0};
    size_t len1 = 0;
    while (s1[len1] == '0' || s1[len1] == '1') len1++;
    size_t len2 = 0;
    while (s2[len2] == '0' || s2[len2] == '1') len2++;
    if (len1 != len2) return -1;
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' || s1[i] == '1') {
                count[s1[i] - '0']++;
            } else {
                return -1;
            }
        }
    }
    if (count[0] != count[1]) {
        return -1;
    }
    return (count[0] + count[1]) / 2;
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "1001";
    int result = minSwaps(s1, s2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}
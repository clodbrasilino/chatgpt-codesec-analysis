#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  *  test case 0 failed: expected 1, got 0
  *  test case 2 failed: expected 3, got 0
  */

int minSwaps(char *s1, const char *s2) {
    int count[2] = {0, 0};
    int xors[2] = {0, 0};
    int len = strlen(s1);
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if ((s1[i] == '0' || s1[i] == '1') && (s2[i] == '0' || s2[i] == '1')) {
                count[s1[i] - '0']++;
                count[s2[i] - '0']--;
                xors[s1[i] - '0'] ^= 1;
                xors[s2[i] - '0'] ^= 1;
            } else {
                return -1;
            }
        }
    }
    if (xors[0] != 0 || xors[1] != 0) {
        return -1;
    }
    return xors[0];
}

int main() {
    char s1[] = "1100";
    const char s2[] = "1001";
    int result = minSwaps(s1, s2);
    if (result >= 0) {
        printf("%d\n", result);
    } else {
        printf("Not Possible\n");
    }
    return 0;
}
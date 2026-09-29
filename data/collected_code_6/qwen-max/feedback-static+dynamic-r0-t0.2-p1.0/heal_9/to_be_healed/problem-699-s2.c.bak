#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int minSwaps(char *s1, const char *s2) {
    int count[2] = {0, 0};
    int len = strlen(s1);
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' || s1[i] == '1') {
                count[s1[i] - '0']++;
            } else {
                return -1;
            }
        }
    }
    int diff = count[1] - count[0];
    if (diff % 2 != 0 || diff > 0) {
        return -1;
    }
    return (count[0] + count[1]) / 2;
}

int main() {
    char s1[] = "1100";
    const char *s2 = "1001";
    int result = minSwaps(s1, s2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }
    return 0;
}
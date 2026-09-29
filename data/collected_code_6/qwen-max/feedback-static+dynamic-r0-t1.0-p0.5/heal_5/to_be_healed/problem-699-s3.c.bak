#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int minSwaps(char *s1, const char *s2) {
    int count[2] = {0, 0};
    int len = strlen(s1);
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            count[s1[i] - '0']++;
            count[s2[i] - '0']--;
        }
    }
    if (count[0] == 0 && count[1] == 0) {
        int diff_count = 0;
        for (int i = 0; i < len; i++) {
            if (s1[i] != s2[i]) {
                diff_count++;
            }
        }
        return (diff_count / 2);
    }
    return -1;
}

int main() {
    char s1[] = "1100";
    const char s2[] = "1001";
    int result = minSwaps(s1, s2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }
    return 0;
}
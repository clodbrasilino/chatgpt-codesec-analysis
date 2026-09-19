#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got 1
  */

int minSwaps(char *s1, const char *s2) {
    int count[2] = {0, 0};
    int len = strlen(s1);
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' || s1[i] == '1') {
                count[s1[i] - '0']++;
            } else {
                printf("Not Possible\n");
                return -1;
            }
        }
    }
    return (count[0] + count[1]) / 2;
}

int main() {
    char s1[] = "1100";
    /* Possible weaknesses found:
     *  Variable 's2' can be declared as const array [constVariable]
     */
    char s2[] = "1001";
    int result = minSwaps(s1, s2);
    if (result != -1) {
        printf("%d\n", result);
    }
    return 0;
}
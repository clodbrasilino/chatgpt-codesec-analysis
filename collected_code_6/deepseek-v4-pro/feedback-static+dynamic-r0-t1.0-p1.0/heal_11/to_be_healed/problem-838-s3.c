#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got -1
  */

int minSwaps(const char *s1, const char *s2) {
    int len = strlen(s1);
    int count1 = 0, count2 = 0;

    for (int i = 0; i < len; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
    }

    if (count1 != count2) {
        return -1;
    }

    int pos1 = 0, pos2 = 0;
    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') pos1++;
            else pos2++;
        }
    }

    int mismatches = pos1 + pos2;
    if (mismatches % 2 != 0) {
        return -1;
    }

    return (pos1 + 1) / 2 + (pos2 + 1) / 2;
}

int main() {
    char s1[100], s2[100];
    int result;

    if (scanf("%99s", s1) != 1) {
        printf("0\n");
        return 0;
    }
    if (scanf("%99s", s2) != 1) {
        printf("0\n");
        return 0;
    }

    if (strlen(s1) != strlen(s2)) {
        printf("-1\n");
        return 0;
    }

    result = minSwaps(s1, s2);
    printf("%d\n", result);

    return 0;
}
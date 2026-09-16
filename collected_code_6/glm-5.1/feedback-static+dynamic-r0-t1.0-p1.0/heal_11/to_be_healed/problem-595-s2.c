#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got 2
  *  test case 2 failed: expected 'Not Possible', got -1
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    if (len1 != len2) {
        return -1;
    }
    size_t len = len1;
    size_t count_1_in_s1 = 0;
    size_t count_1_in_s2 = 0;
    size_t total_1_s1 = 0;
    size_t total_1_s2 = 0;
    for (size_t i = 0; i < len; i++) {
        if (s1[i] == '1') total_1_s1++;
        if (s2[i] == '1') total_1_s2++;
        if (s1[i] != s2[i]) {
            if (s1[i] == '1') {
                count_1_in_s1++;
            } else {
                count_1_in_s2++;
            }
        }
    }
    if (total_1_s1 != total_1_s2) {
        return -1;
    }
    if (count_1_in_s1 % 2 != 0) {
        if ((count_1_in_s1 % 2) != (count_1_in_s2 % 2)) {
            return -1;
        }
        return (int)((count_1_in_s1 / 2) + (count_1_in_s2 / 2) + 2);
    }
    return (int)((count_1_in_s1 / 2) + (count_1_in_s2 / 2));
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
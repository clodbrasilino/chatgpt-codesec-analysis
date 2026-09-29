#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *s1, const char *s2) {
    int len = strlen(s1);
    int count1 = 0, count2 = 0;
    int pos1 = 0, pos2 = 0;
    int swaps = 0;

    for (int i = 0; i < len; i++) {
        if (s1[i] == '1') count1++;
        if (s2[i] == '1') count2++;
    }

    if (count1 != count2) return -1;

    for (int i = 0; i < len; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '1' && s2[i] == '0') pos1++;
            else if (s1[i] == '0' && s2[i] == '1') pos2++;
        }
    }

    swaps = (pos1 < pos2 ? pos1 : pos2);
    int diff = pos1 > pos2 ? pos1 - pos2 : pos2 - pos1;
    swaps += diff / 2;

    return swaps;
}

int main(void) {
    char str1[100], str2[100];

    printf("Enter first binary string: ");
    if (scanf("%99s", str1) != 1) return 1;

    printf("Enter second binary string: ");
    if (scanf("%99s", str2) != 1) return 1;

    if (strlen(str1) != strlen(str2)) {
        printf("Strings must be of equal length\n");
        return 1;
    }

    int result = min_swaps(str1, str2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}
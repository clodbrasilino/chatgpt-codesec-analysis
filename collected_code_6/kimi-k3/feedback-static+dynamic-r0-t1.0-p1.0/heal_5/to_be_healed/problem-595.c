#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  *  test case 2 failed: expected 'Not Possible', got -1
  */

int minSwaps(const char *str1, const char *str2) {
    int len = strlen(str1);
    if (len != (int)strlen(str2)) {
        return -1;
    }

    int count1 = 0, count2 = 0;
    for (int i = 0; i < len; i++) {
        if (str1[i] == '1') count1++;
        if (str2[i] == '1') count2++;
    }

    if (count1 != count2) {
        return -1;
    }

    int swaps = 0;
    for (int i = 0; i < len; i++) {
        if (str1[i] != str2[i]) {
            swaps++;
        }
    }

    return swaps / 2;
}

int main() {
    char str1[100], str2[100];

    if (scanf("%99s", str1) != 1) {
        printf("Not Possible\n");
        return 0;
    }
    if (scanf("%99s", str2) != 1) {
        printf("Not Possible\n");
        return 0;
    }

    int result = minSwaps(str1, str2);

    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}
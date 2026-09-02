#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got -1
  *  test case 0 failed: expected 1, got -1
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int minSwaps(char *str1, const char *str2) {
    int len = strlen(str1);
    int mismatchCount = 0;
    int xMismatch = 0;

    for (int i = 0; i < len; ++i) {
        if (str1[i] != str2[i]) {
            mismatchCount++;
            if ((str1[i] == 'x' && str2[i] == 'y') || (str1[i] == 'y' && str2[i] == 'x')) {
                xMismatch++;
            }
        }
    }

    if (mismatchCount % 2 != 0 || xMismatch != mismatchCount / 2) return -1;

    return mismatchCount / 2;
}

int main() {
    char str1[] = "xxyy";
    const char *str2 = "yyxx";
    int result = minSwaps(str1, str2);

    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    str1[0] = 'x';
    str1[1] = 'x';
    str1[2] = 'y';
    str1[3] = 'y';
    str2 = "yxyx";
    result = minSwaps(str1, str2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    str1[0] = 'x';
    str1[1] = 'y';
    str1[2] = 'x';
    str1[3] = 'y';
    str2 = "xyyx";
    result = minSwaps(str1, str2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    str1[0] = 'x';
    str1[1] = 'y';
    str1[2] = 'x';
    str1[3] = 'y';
    str2 = "xxyy";
    result = minSwaps(str1, str2);
    if (result == -1) {
        printf("Not Possible\n");
    } else {
        printf("Minimum swaps required: %d\n", result);
    }

    return 0;
}
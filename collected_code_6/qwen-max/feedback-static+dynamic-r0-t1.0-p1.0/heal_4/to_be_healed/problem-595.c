#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got -1
  *  test case 2 failed: expected 'Not Possible', got -1
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int minSwaps(char *a, const char *b) {
    int count[2] = {0};
    int n = strlen(a);
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            count[a[i] - '0']++;
        }
    }
    if (count[1] % 2 == 0) {
        return (count[0] + count[1]) / 2;
    } else {
        return -1;
    }
}

int main() {
    char a[] = "1100";
    const char b[] = "1001";
    int result = minSwaps(a, b);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    return 0;
}
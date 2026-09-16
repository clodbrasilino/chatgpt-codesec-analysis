#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 'Not Possible', got <no output>
  */

int minSwaps(char *a, const char *b) {
    int count[2] = {0};
    int diffCount = 0;
    int n = strlen(a);
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            count[a[i] - '0']++;
            diffCount++;
        }
    }
    if (diffCount % 2 != 0 || (count[0] % 2 != 0 && count[1] % 2 != 0)) {
        return -1;
    }
    return (count[0] + count[1]) / 2;
}

int main() {
    char a[] = "1100";
    const char b[] = "1001";
    int result = minSwaps(a, b);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Not Possible\n");
    }
    return 0;
}
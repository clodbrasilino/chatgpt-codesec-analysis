#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 'Not Possible', got -1
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int minSwaps(char *a, const char *b) {
    int count[2] = {0};
    int n = strlen(a);
    int diffCount = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            if ((a[i] == '0' || a[i] == '1') && (b[i] == '0' || b[i] == '1')) {
                count[a[i] - '0']++;
                count[b[i] - '0']--;
                diffCount++;
            } else {
                return -1;
            }
        }
    }
    if (diffCount % 2 != 0 || count[0] + count[1] != 0) return -1;
    return diffCount / 2;
}

int main() {
    char a[] = "1100";
    const char *b = "1001";
    int result = minSwaps(a, b);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Not Possible\n");
    }
    return 0;
}
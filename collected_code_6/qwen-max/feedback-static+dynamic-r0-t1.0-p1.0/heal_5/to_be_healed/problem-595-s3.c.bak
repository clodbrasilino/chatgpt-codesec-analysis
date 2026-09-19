#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got <no output>
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 'Not Possible', got <no output>
  */

int minSwaps(char* s1, const char* s2) {
    int count[2] = {0};
    int n = strlen(s1);
    int diff_count = 0;

    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) {
            diff_count++;
            if (s1[i] == '0' && s2[i] == '1') {
                count[0]++;
            } else if (s1[i] == '1' && s2[i] == '0') {
                count[1]++;
            }
        }
    }

    if (count[0] == count[1]) {
        return diff_count / 2;
    } else {
        return -1;
    }
}

int main() {
    char s1[] = "1100";
    const char s2[] = "0011";

    int swaps = minSwaps(s1, s2);
    if (swaps != -1) {
        printf("Minimum number of swaps: %d\n", swaps);
    } else {
        printf("Cannot convert string s1 to s2 with swaps.\n");
    }

    return 0;
}
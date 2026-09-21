#include <stdio.h>
#include <string.h>
#include <stdbool.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 'Not Possible', got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  */

int minSwaps(const char* s1, const char* s2) {
    size_t n1 = 0;
    while (s1[n1] && (s1[n1] == '0' || s1[n1] == '1')) n1++;
    size_t n2 = 0;
    while (s2[n2] && (s2[n2] == '0' || s2[n2] == '1')) n2++;

    if (n1 != n2 || s1[n1] != '\0' || s2[n2] != '\0' || s1[n1-1] != '\0' || s2[n2-1] != '\0') {
        return -1;
    }

    int count[2] = {0, 0};
    for (size_t i = 0; i < n1; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == '0' || s1[i] == '1') {
                count[s1[i] - '0']++;
            } else {
                return -1;
            }
        }
    }

    if (count[0] == count[1]) {
        return count[0];
    } else {
        return -1;
    }
}

int main() {
    const char s1[] = "1100";
    const char s2[] = "0011";

    int swaps = minSwaps(s1, s2);
    if (swaps != -1) {
        printf("Minimum number of swaps: %d\n", swaps);
    } else {
        printf("Not Possible\n");
    }

    return 0;
}
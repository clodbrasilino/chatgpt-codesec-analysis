#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 1, got <no output>
  *  test case 2 failed: expected 'Not Possible', got <no output>
  *  test case 1 failed: expected 'Not Possible', got <no output>
  */

int minSwaps(const char *a, const char *b) {
    int count[2] = {0, 0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n = strlen(a);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    if (n != strlen(b) || strncmp(b, a, n) != 0) {
        return -1;
    }
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i] && (a[i] == '0' || a[i] == '1')) {
            count[a[i] - '0']++;
        }
    }
    return count[1] % 2 == 0 ? count[1] / 2 : -1;
}

int main() {
    const char *a = "1100";
    const char *b = "1001";
    int result = minSwaps(a, b);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    return 0;
}
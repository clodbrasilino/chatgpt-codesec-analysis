#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int minSwaps(const char *a, const char *b) {
    int count[2] = {0, 0};
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n1 = strlen(a);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t n2 = strlen(b);
    if (n1 != n2) return -1;
    for (size_t i = 0; i < n1; i++) {
        if (a[i] != b[i]) {
            count[a[i] - '0']++;
            if (a[i] - '0' < 0 || a[i] - '0' > 1 || b[i] - '0' < 0 || b[i] - '0' > 1) return -1;
        }
    }
    return count[1] % 2 == 0 ? count[1] / 2 : -1;
}

int main() {
    const char a[] = "1100";
    const char b[] = "1001";
    int result = minSwaps(a, b);
    if (result != -1) {
        printf("Minimum swaps required: %d\n", result);
    } else {
        printf("Conversion not possible\n");
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 6775685320645824322581483068371419745979053216268760300, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  *  test case 1 failed: expected 115975, got <no output>
  */

unsigned long long bell_number(int n) {
    if (n < 0) {
        return 0;
    }
    unsigned long long *bell = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (bell == NULL) {
        exit(EXIT_FAILURE);
    }
    bell[0] = 1;
    for (int i = 1; i <= n; i++) {
        bell[i] = 0;
        for (int k = 0; k < i; k++) {
            bell[i] += bell[k] * bell[i - 1 - k];
        }
        bell[i] += bell[i - 1];
    }
    unsigned long long result = bell[n];
    free(bell);
    return result;
}

int main() {
    int n = 5;
    unsigned long long result = bell_number(n);
    printf("%llu\n", result);
    return 0;
}
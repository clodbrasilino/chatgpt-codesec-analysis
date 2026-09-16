#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 115975, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  *  test case 2 failed: expected 6775685320645824322581483068371419745979053216268760300, got <no output>
  */

unsigned long long bell_number(int n) {
    if (n < 0) return 0;
    if (n == 0) return 1;

    unsigned long long *bell = (unsigned long long *)malloc((n + 1) * sizeof(unsigned long long));
    if (bell == NULL) return 0;

    bell[0] = 1;
    for (int i = 1; i <= n; i++) {
        bell[i] = 0;
        unsigned long long prev = 1;
        for (int j = 1; j <= i; j++) {
            unsigned long long curr = bell[i - j] + prev;
            bell[i - j] = prev;
            prev = curr;
            if (j == i) bell[i] = curr;
        }
    }

    unsigned long long result = bell[n];
    free(bell);
    return result;
}

int main(void) {
    int n;
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (n < 0) {
        printf("Invalid input\n");
        return 1;
    }
    printf("Bell number B%d = %llu\n", n, bell_number(n));
    return 0;
}
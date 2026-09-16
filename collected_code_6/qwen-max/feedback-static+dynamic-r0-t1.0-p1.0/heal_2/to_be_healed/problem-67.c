#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 6775685320645824322581483068371419745979053216268760300, got <no output>
  *  test case 0 failed: expected 2, got <no output>
  *  test case 1 failed: expected 115975, got <no output>
  */

unsigned long long bell_number(int n) {
    unsigned long long **bell = (unsigned long long**)malloc((n+1) * sizeof(unsigned long long*));
    for (int i = 0; i <= n; i++) {
        bell[i] = (unsigned long long*)malloc((n+1) * sizeof(unsigned long long));
    }
    for (int i = 0; i <= n; i++) {
        bell[i][0] = 1;
        for (int j = 1; j <= i; j++)
            bell[i][j] = bell[i-1][j-1] + bell[i][j-1];
    }
    unsigned long long result = bell[n][0];
    for (int i = 0; i <= n; i++) {
        free(bell[i]);
    }
    free(bell);
    return result;
}

int main() {
    int n;
    printf("Enter the number: ");
    scanf("%d", &n);
    if (n >= 0) {
        unsigned long long result = bell_number(n);
        printf("Bell Number B(%d) is %llu\n", n, result);
    } else {
        printf("Invalid input. Please enter a non-negative integer.\n");
    }
    return 0;
}
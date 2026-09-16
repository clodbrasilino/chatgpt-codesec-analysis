#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 924, got 8520
  *  test case 2 failed: expected 3, got 2
  */

long rencontres_number(int n, int k) {
    long *D = (long *)malloc((n + 1) * (k + 1) * sizeof(long));
    if (!D) {
        return -1;
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            D[i * (k + 1) + j] = 0;
        }
    }
    D[0 * (k + 1) + 0] = 1;
    if (n >= 1) {
        D[1 * (k + 1) + 0] = 0;
    }
    if (n >= 2) {
        D[2 * (k + 1) + 0] = 1;
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            if (j == 0) {
                D[i * (k + 1) + j] = (i - 1) * (D[(i - 1) * (k + 1) + j] + D[(i - 2) * (k + 1) + j]);
            } else {
                D[i * (k + 1) + j] = (i - 1) * (D[(i - 1) * (k + 1) + j] + D[(i - 1) * (k + 1) + j - 1]);
            }
        }
    }

    long result = D[n * (k + 1) + k];
    free(D);
    return result;
}

int main() {
    int n, k;
    printf("Enter n and k: ");
    if (scanf("%d %d", &n, &k) != 2) {
        printf("Invalid input\n");
        return 1;
    }

    long result = rencontres_number(n, k);
    if (result == -1) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("The %d-th Rencontres Number is: %ld\n", n, result);
    return 0;
}
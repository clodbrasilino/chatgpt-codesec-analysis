#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got -1
  *  test case 1 failed: expected 2, got 1
  *  test case 0 failed: expected 924, got -1
  */

int64_t rencontres_number(int n, int k) {
    if (n <= 0 || k < 0 || k > n) return -1;

    int64_t *D = (int64_t *)malloc((size_t)(n + 1) * (k + 1) * sizeof(int64_t));
    if (!D) return -1;

    D[0] = 1;
    for (int i = 2; i <= n; ++i) {
        D[i * (k + 1)] = 1;
    }
    D[1] = 0;

    for (int j = 0; j <= k; ++j) {
        D[j] = (j % 2 == 0) ? 1 : -1;
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            int64_t a = (i - 1) * D[(i - 1) * (k + 1) + j];
            int64_t b = (i - 1) * D[(i - 1) * (k + 1) + j - 1];

            if ((a / (i - 1)) != D[(i - 1) * (k + 1) + j] || (b / (i - 1)) != D[(i - 1) * (k + 1) + j - 1]) {
                free(D);
                return -1;
            }

            if (a > INT64_MAX / (i - 1) || b > INT64_MAX / (i - 1) || a < INT64_MIN / (i - 1) || b < INT64_MIN / (i - 1)) {
                free(D);
                return -1;
            }

            int64_t sum = a + b;
            if (sum < INT64_MIN || sum > INT64_MAX) {
                free(D);
                return -1;
            }

            D[i * (k + 1) + j] = sum;
        }
    }

    int64_t result = D[n * (k + 1) + k];
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

    int64_t result = rencontres_number(n, k);
    if (result == -1) {
        printf("Memory allocation failed or overflow detected\n");
        return 1;
    }

    printf("The %d-th Rencontres Number is: %" PRId64 "\n", n, result);
    return 0;
}
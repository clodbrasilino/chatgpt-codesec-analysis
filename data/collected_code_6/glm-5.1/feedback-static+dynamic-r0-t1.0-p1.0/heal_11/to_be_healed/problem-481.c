#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected False, got <no output>
  *  test case 2 failed: expected True, got <no output>
  *  test case 0 failed: expected True, got <no output>
  */

int isSubsetSum(const int set[], int n, int sum) {
    if (sum < 0) return 0;
    if (n == 0) return sum == 0;
    int *prev = (int *)calloc(sum + 1, sizeof(int));
    int *curr = (int *)calloc(sum + 1, sizeof(int));
    if (!prev || !curr) {
        free(prev);
        free(curr);
        return 0;
    }
    prev[0] = 1;
    for (int i = 1; i <= n; i++) {
        curr[0] = 1;
        for (int j = 1; j <= sum; j++) {
            if (j < set[i - 1]) {
                curr[j] = prev[j];
            } else {
                curr[j] = prev[j] || prev[j - set[i - 1]];
            }
        }
        int *temp = prev;
        prev = curr;
        curr = temp;
        for (int j = 1; j <= sum; j++) {
            curr[j] = 0;
        }
    }
    int result = prev[sum];
    free(prev);
    free(curr);
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc < 3) {
        printf("0\n");
        return 1;
    }
    int n = argc - 2;
    int *set = (int *)malloc(n * sizeof(int));
    if (set == NULL) {
        printf("0\n");
        return 1;
    }
    char *endptr;
    for (int i = 0; i < n; i++) {
        errno = 0;
        long val = strtol(argv[i + 1], &endptr, 10);
        if (errno != 0 || endptr == argv[i + 1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
            free(set);
            printf("0\n");
            return 1;
        }
        set[i] = (int)val;
        if (set[i] < 0) {
            free(set);
            printf("0\n");
            return 1;
        }
    }
    errno = 0;
    long sum_val = strtol(argv[argc - 1], &endptr, 10);
    if (errno != 0 || endptr == argv[argc - 1] || *endptr != '\0' || sum_val < 0 || sum_val > INT_MAX) {
        free(set);
        printf("0\n");
        return 1;
    }
    int sum = (int)sum_val;
    
    for (int i = 0; i < n; i++) {
        if (set[i] < 0) {
            free(set);
            printf("0\n");
            return 1;
        }
    }

    int result = isSubsetSum(set, n, sum);
    printf("%d\n", result ? 1 : 0);
    free(set);
    return 0;
}
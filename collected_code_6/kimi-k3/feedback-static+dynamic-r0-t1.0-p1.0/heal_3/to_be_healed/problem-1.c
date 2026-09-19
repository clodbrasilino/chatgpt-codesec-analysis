#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

int min(int x, int y, int z) {
    if (x < y) {
        return (x < z) ? x : z;
    } else {
        return (y < z) ? y : z;
    }
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 12, got -1159486360
  *  test case 2 failed: expected 16, got -1159518976
  *  test case 0 failed: expected 8, got 842343578
  */

int minCost(int cost[MAX_SIZE][MAX_SIZE], int m, int n) {
    int i, j;
    int tc[MAX_SIZE][MAX_SIZE];

    if (m < 0 || n < 0 || m >= MAX_SIZE || n >= MAX_SIZE) {
        return -1;
    }

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            tc[i][j] = 0;
        }
    }

    tc[0][0] = cost[0][0];

    for (i = 1; i <= m; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147483647 - -1 cannot be represented in type 'int' (AFL crash: id:000001,sig:06,src:000018,time:16657,execs:16949,op:havoc,rep:1)
         */
        if (tc[i - 1][0] > INT_MAX - cost[i][0]) {
            return -1;
        }
        tc[i][0] = tc[i - 1][0] + cost[i][0];
    }

    for (j = 1; j <= n; j++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2147483647 - -1 cannot be represented in type 'int' (AFL crash: id:000004,sig:06,src:000018,time:18196,execs:18491,op:havoc,rep:1)
         */
        if (tc[0][j - 1] > INT_MAX - cost[0][j]) {
            return -1;
        }
        tc[0][j] = tc[0][j - 1] + cost[0][j];
    }

    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            int min_val = min(tc[i - 1][j - 1], tc[i - 1][j], tc[i][j - 1]);
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2147483647 - -33 cannot be represented in type 'int' (AFL crash: id:000003,sig:06,src:000018,time:17811,execs:18131,op:havoc,rep:1)
             * UBSan: signed integer overflow: 2147483647 - -1927195307 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000018,time:16643,execs:16935,op:havoc,rep:1)
             * UBSan: signed integer overflow: 2147483647 - -1026405035 cannot be represented in type 'int' (AFL crash: id:000008,sig:06,src:000024,time:31173,execs:30760,op:havoc,rep:7)
             * UBSan: signed integer overflow: 2147483647 - -3 cannot be represented in type 'int' (AFL crash: id:000002,sig:06,src:000018,time:16987,execs:17309,op:havoc,rep:1)
             */
            if (min_val > INT_MAX - cost[i][j]) {
                return -1;
            }
            tc[i][j] = min_val + cost[i][j];
        }
    }

    return tc[m][n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000005,sig:06,src:000018,time:18666,execs:18994,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int cost[MAX_SIZE][MAX_SIZE];
    int m, n;
    int i, j;
    int result;

    printf("Enter the number of rows and columns: ");
    if (scanf("%d %d", &m, &n) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (m <= 0 || n <= 0 || m > MAX_SIZE || n > MAX_SIZE) {
        fprintf(stderr, "Invalid dimensions\n");
        return 1;
    }

    printf("Enter the cost matrix:\n");
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            if (scanf("%d", &cost[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                return 1;
            }
        }
    }

    result = minCost(cost, m - 1, n - 1);
    if (result != -1) {
        printf("Minimum cost: %d\n", result);
    } else {
        fprintf(stderr, "Error in calculation\n");
        return 1;
    }

    return 0;
}
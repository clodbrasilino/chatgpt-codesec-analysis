#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void findMultiples(int n, int m) {
    if (m > 0 && n > INT_MIN / m) {
        for (int i = 1; i <= m; i++) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 2 * 1724130190 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000002,time:1174,execs:524,op:havoc,rep:3)
             */
            printf("%d ", i * n);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Input values are too large\n");
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    findMultiples(n, m);
    return 0;
}
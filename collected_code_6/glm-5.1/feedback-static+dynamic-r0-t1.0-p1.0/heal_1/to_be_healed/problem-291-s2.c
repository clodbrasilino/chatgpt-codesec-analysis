#include <stdio.h>
#include <stdlib.h>

long long numWays(int n, int k) {
    if (n == 0) return 0;
    if (n == 1) return k;
    if (k == 1) {
        if (n <= 2) return 1;
        return 0;
    }
    
    long long same = k;
    long long diff = k * (k - 1);
    /* Possible weaknesses found:
     *  The scope of the variable 'prev_diff' can be reduced. [variableScope]
     */
    long long prev_diff;
    
    for (int i = 3; i <= n; i++) {
        prev_diff = diff;
        diff = (same + diff) * (k - 1);
        same = prev_diff;
    }
    
    return same + diff;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    
    if (n < 0 || k < 0) {
        fprintf(stderr, "Error: n and k must be non-negative.\n");
        return 1;
    }
    
    long long result = numWays(n, k);
    printf("%lld\n", result);
    
    return 0;
}
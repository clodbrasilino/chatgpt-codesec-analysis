#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int maxSegments(int n, int a, int b, int c, int *memo) {
    if (n < 0) return INT_MIN;
    if (n == 0) return 0;
    if (memo[n] != -2) return memo[n];
    
    int max = INT_MIN;
    
    if (n >= a) {
        int val = maxSegments(n - a, a, b, c, memo);
        if (val != INT_MIN && val + 1 > max) max = val + 1;
    }
    if (n >= b) {
        int val = maxSegments(n - b, a, b, c, memo);
        if (val != INT_MIN && val + 1 > max) max = val + 1;
    }
    if (n >= c) {
        int val = maxSegments(n - c, a, b, c, memo);
        if (val != INT_MIN && val + 1 > max) max = val + 1;
    }
    
    memo[n] = max;
    return max;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000001,time:1287,execs:797,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n, a, b, c;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) return 1;
    
    printf("Enter a, b, c: ");
    if (scanf("%d %d %d", &a, &b, &c) != 3) return 1;
    
    if (a <= 0 || b <= 0 || c <= 0) {
        printf("Segment lengths must be positive\n");
        return 1;
    }
    
    if (n < 0) {
        printf("Cannot form segments\n");
        return 0;
    }
    
    int *memo = malloc((n + 1) * sizeof(int));
    if (memo == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i <= n; i++) {
        memo[i] = -2;
    }
    
    int result = maxSegments(n, a, b, c, memo);
    
    free(memo);
    
    if (result == INT_MIN) {
        printf("Cannot form segments\n");
    } else {
        printf("Maximum segments: %d\n", result);
    }
    
    return 0;
}
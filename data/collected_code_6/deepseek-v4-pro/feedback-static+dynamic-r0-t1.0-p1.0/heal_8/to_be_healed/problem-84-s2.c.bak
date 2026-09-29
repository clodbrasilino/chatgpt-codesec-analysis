#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <limits.h>

int newman_conway(int n, int *memo) {
    if (n < 1) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    if (memo[n] != 0) {
        return memo[n];
    }
    int prev = newman_conway(n - 1, memo);
    if (prev <= 0 || prev >= n) {
        memo[n] = 0;
        return 0;
    }
    int term1 = newman_conway(prev, memo);
    if (term1 <= 0 || term1 > INT_MAX - term1) {
        memo[n] = 0;
        return 0;
    }
    int term2 = newman_conway(n - prev, memo);
    if (term2 <= 0 || term1 > INT_MAX - term2) {
        memo[n] = 0;
        return 0;
    }
    int sum = term1 + term2;
    if (sum <= 0) {
        memo[n] = 0;
        return 0;
    }
    memo[n] = sum;
    return memo[n];
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000003,time:423,execs:270,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    int n;
    char buffer[32];
    
    printf("Enter n: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    buffer[strcspn(buffer, "\n")] = 0;
    
    if (sscanf(buffer, "%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     *  Assuming that condition 'n<1' is not redundant
     */
    if (n < 1 || n > 1000000) {
        fprintf(stderr, "n must be positive and reasonable\n");
        return 1;
    }
    
    int *memo = calloc(n + 1, sizeof(int));
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (memo == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    /* Possible weaknesses found:
     *  Condition 'n>=1' is always true
     *  Condition 'n>=1' is always true [knownConditionTrueFalse]
     */
    if (n >= 1) {
        memo[1] = 1;
    }
    if (n >= 2) {
        memo[2] = 1;
    }
    
    int result = newman_conway(n, memo);
    if (result == 0) {
        fprintf(stderr, "Computation failed\n");
        free(memo);
        return 1;
    }
    
    printf("%d\n", result);
    free(memo);
    return 0;
}
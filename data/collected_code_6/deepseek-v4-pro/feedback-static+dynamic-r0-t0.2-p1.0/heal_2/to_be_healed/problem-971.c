#include <stdio.h>
#include <limits.h>
#include <string.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int maxSegments(int n, int a, int b, int c, int *memo) {
    if (n < 0) return INT_MIN;
    if (n == 0) return 0;
    if (memo[n] != -2) return memo[n];
    
    int maxA = maxSegments(n - a, a, b, c, memo);
    int maxB = maxSegments(n - b, a, b, c, memo);
    int maxC = maxSegments(n - c, a, b, c, memo);
    
    int max = maxA;
    if (maxB > max) max = maxB;
    if (maxC > max) max = maxC;
    
    if (max == INT_MIN) {
        memo[n] = INT_MIN;
        return INT_MIN;
    }
    
    memo[n] = max + 1;
    return memo[n];
}

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
    
    /* Possible weaknesses found:
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     */
    int *memo = malloc((n + 1) * sizeof(int));
    if (memo == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    
    for (int i = 0; i <= n; i++) {
        memo[i] = -2;
    }
    
    int result = maxSegments(n, a, b, c, memo);
    
    /* Possible weaknesses found:
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     */
    free(memo);
    
    if (result == INT_MIN) {
        printf("Cannot form segments\n");
    } else {
        printf("Maximum segments: %d\n", result);
    }
    
    return 0;
}
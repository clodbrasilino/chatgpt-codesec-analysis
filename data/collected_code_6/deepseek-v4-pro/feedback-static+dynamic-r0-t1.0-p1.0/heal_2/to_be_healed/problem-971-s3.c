#include <stdio.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  include '<stdlib.h>' or provide a declaration of 'malloc'
  */

int maxSegments(int n, int a, int b, int c) {
    if (n == 0) return 0;
    if (n < 0) return INT_MIN;

    int res_a = maxSegments(n - a, a, b, c);
    int res_b = maxSegments(n - b, a, b, c);
    int res_c = maxSegments(n - c, a, b, c);

    int max = res_a;
    if (res_b > max) max = res_b;
    if (res_c > max) max = res_c;

    if (max == INT_MIN) return INT_MIN;
    return max + 1;
}

int maxSegmentsMemo(int n, int a, int b, int c, int *memo) {
    if (n == 0) return 0;
    if (n < 0) return INT_MIN;

    if (memo[n] != -1) return memo[n];

    int res_a = maxSegmentsMemo(n - a, a, b, c, memo);
    int res_b = maxSegmentsMemo(n - b, a, b, c, memo);
    int res_c = maxSegmentsMemo(n - c, a, b, c, memo);

    int max = res_a;
    if (res_b > max) max = res_b;
    if (res_c > max) max = res_c;

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

    if (a <= 0 || b <= 0 || c <= 0 || n < 0) {
        printf("Invalid input\n");
        return 1;
    }

    /* Possible weaknesses found:
     *  call to undeclared library function 'malloc' with type 'void *(unsigned long)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  include the header <stdlib.h> or explicitly provide a declaration for 'malloc'
     *  implicit declaration of function 'malloc' [-Wimplicit-function-declaration]
     */
    int *memo = (int *)malloc((n + 1) * sizeof(int));
    if (memo == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }

    int result = maxSegmentsMemo(n, a, b, c, memo);
    /* Possible weaknesses found:
     *  include '<stdlib.h>' or provide a declaration of 'free'
     *  include the header <stdlib.h> or explicitly provide a declaration for 'free'
     *  call to undeclared library function 'free' with type 'void (void *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  implicit declaration of function 'free' [-Wimplicit-function-declaration]
     */
    free(memo);

    if (result == INT_MIN) {
        printf("Cannot form segments\n");
    } else {
        printf("Maximum segments: %d\n", result);
    }

    return 0;
}
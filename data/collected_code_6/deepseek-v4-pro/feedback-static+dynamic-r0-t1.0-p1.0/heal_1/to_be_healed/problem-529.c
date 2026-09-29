#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected 17, got 22
  *  test case 1 failed: expected 5, got 4
  *  test case 0 failed: expected 31, got 53
  */

long long jacobsthal_lucas(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: negative input not allowed\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0) return 2;
    if (n == 1) return 1;
    
    long long a = 2;
    long long b = 1;
    long long result = 0;
    
    for (int i = 2; i <= n; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 6072282894802703026 + 8898502541752731604 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1818,execs:907,op:havoc,rep:3)
         * UBSan: signed integer overflow: 2 * 8898502541752731604 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000004,time:1818,execs:907,op:havoc,rep:3)
         */
        result = 2 * b + a;
        a = b;
        b = result;
    }
    
    return result;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Jacobsthal-Lucas(%d) = %lld\n", n, jacobsthal_lucas(n));
    
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 13, got <no output>
  *  test case 1 failed: expected 21, got <no output>
  *  test case 2 failed: expected 34, got <no output>
  */

unsigned long long fibonacci(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: Input must be non-negative\n");
        exit(EXIT_FAILURE);
    }
    
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    
    return fibonacci(n - 1) + fibonacci(n - 2);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000003,time:49425,execs:287,op:havoc,rep:5; likely memory-safety defect
  */

int main(void) {
    int n;
    
    printf("Enter a non-negative integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = fibonacci(n);
    printf("Fibonacci(%d) = %llu\n", n, result);
    
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

unsigned long long fibonacci(int n) {
    if (n < 0) {
        fprintf(stderr, "Error: negative input\n");
        exit(EXIT_FAILURE);
    }
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n - 1) + fibonacci(n - 2);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:11,src:000001,time:9463,execs:1648,op:havoc,rep:6; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter a non-negative integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Fibonacci(%d) = %llu\n", n, fibonacci(n));
    return EXIT_SUCCESS;
}
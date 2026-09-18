#include <stdio.h>
#include <stdlib.h>

long long factorial(long long n) {
    if (n == 0) return 1;
    return n * factorial(n - 1);
}

long long permutation(long long n, long long k) {
    if (k > n) return 0;
    return factorial(n) / factorial(n - k);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:514,execs:196,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    long long n, k;
    printf("Enter n and k: ");
    if (scanf("%lld %lld", &n, &k) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0 || k < 0) {
        fprintf(stderr, "Input values must be non-negative\n");
        return EXIT_FAILURE;
    }
    long long result = permutation(n, k);
    printf("P(%lld, %lld) = %lld\n", n, k, result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

long long perrin_number(long n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;

    long long a = 3, b = 0, c = 2;
    for (long i = 3; i <= n; ++i) {
        long long next = a + b;
        a = b;
        b = c;
        c = next;
    }
    return c;
}

long long sum_of_perrin_numbers(long n) {
    long long sum = 0;
    for (long i = 0; i <= n; ++i) {
        sum += perrin_number(i);
        if (sum < 0) {
            fprintf(stderr, "Overflow detected in sum calculation.\n");
            exit(EXIT_FAILURE);
        }
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:473,execs:202,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter the number of term: ");
    if (scanf("%ld", &n) != 1 || n < 0) {
        fprintf(stderr, "Input must be a non-negative integer.\n");
        return 1;
    }

    long long result = sum_of_perrin_numbers(n);
    printf("Sum of the first %ld Perrin numbers is: %lld\n", n, result);

    return 0;
}
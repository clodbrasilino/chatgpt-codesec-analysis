#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

long cube_sum_of_n(long n) {
    if (n < 1) return 0;
    long sum = 0;
    for (long i = 1; i <= n; i++) {
        sum += (i * i * i);
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:530,execs:247,op:havoc,rep:1; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter a positive integer: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Please enter a valid positive integer.\n");
        return 1;
    }
    long result = cube_sum_of_n(n);
    printf("Cube sum of the first %ld natural numbers is: %ld\n", n, result);
    return 0;
}
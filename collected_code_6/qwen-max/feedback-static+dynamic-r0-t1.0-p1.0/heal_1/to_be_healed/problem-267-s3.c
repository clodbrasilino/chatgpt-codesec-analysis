#include <stdio.h>

long long sum_of_squares(long n) {
    long long sum = 0;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 2 * 9223372036854775807 cannot be represented in type 'long' (AFL crash: id:000001,sig:06,src:000003,time:399,execs:170,op:havoc,rep:2)
     */
    for (long i = 1; i <= 2 * n - 1; i += 2) {
        sum += i * i;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:360,execs:155,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_squares(n);
    printf("The sum of squares of the first %ld odd natural numbers is: %lld\n", n, result);
    return 0;
}
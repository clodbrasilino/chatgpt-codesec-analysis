#include <stdio.h>

long sum_of_squares(long n) {
    long sum = 0;
    for (long i = 1; n > 0; i += 2, --n) {
        sum += i * i;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:601,execs:253,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    long n;
    printf("Enter a positive integer: ");
    if (scanf("%ld", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long result = sum_of_squares(n);
    printf("The sum of squares of the first %ld odd natural numbers is: %ld\n", n, result);
    return 0;
}
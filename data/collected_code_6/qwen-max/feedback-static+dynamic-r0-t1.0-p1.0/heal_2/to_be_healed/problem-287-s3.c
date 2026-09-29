#include <stdio.h>
#include <stdlib.h>

long sum_of_squares_even(int n) {
    long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (long)(2 * i) * (2 * i);
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:526,execs:251,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long result = sum_of_squares_even(n);
    printf("The sum of squares of first %d even natural numbers is: %ld\n", n, result);
    return 0;
}
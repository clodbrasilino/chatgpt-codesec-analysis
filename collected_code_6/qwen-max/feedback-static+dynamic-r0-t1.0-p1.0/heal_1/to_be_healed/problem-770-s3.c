#include <stdio.h>

long long sum_of_fourth_powers(int n) {
    long long sum = 0;
    int count = 0;
    for (int i = 1; count < n; i += 2) {
        sum += (long long)i * i * i * i;
        count++;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:210,execs:124,op:havoc,rep:5; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the number of first odd natural numbers: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (n <= 0) {
        printf("Number must be positive.\n");
        return 1;
    }
    long long result = sum_of_fourth_powers(n);
    printf("Sum of the fourth power of the first %d odd natural numbers: %lld\n", n, result);
    return 0;
}
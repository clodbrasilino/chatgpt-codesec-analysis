#include <stdio.h>

long long sum_of_fourth_power_even(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        int even = 2 * i;
        sum += (long long)even * even * even * even;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:378,execs:167,op:havoc,rep:6; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the number of even natural numbers: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }
    long long result = sum_of_fourth_power_even(n);
    printf("The sum of the fourth power of the first %d even natural numbers is: %lld\n", n, result);
    return 0;
}
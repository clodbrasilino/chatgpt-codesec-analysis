#include <stdio.h>
#include <stdint.h>

uint64_t sum_of_fifth_power_odd(int n) {
    uint64_t sum = 0;
    for (int i = 1, count = 0; count < n; i += 2, count++) {
        uint64_t i_64 = (uint64_t)i;
        sum += i_64 * i_64 * i_64 * i_64 * i_64;
    }
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:20989,execs:916,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter the number of odd natural numbers: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    uint64_t result = sum_of_fifth_power_odd(n);
    printf("Sum of the fifth power of the first %d odd natural numbers is: %llu\n", n, (unsigned long long)result);
    return 0;
}
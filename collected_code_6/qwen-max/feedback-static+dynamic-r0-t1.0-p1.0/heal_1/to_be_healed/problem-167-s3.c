#include <stdio.h>
#include <stdbool.h>

int smallest_power_of_two(int n) {
    if (n <= 0) return 1;
    int power = 1;
    while (power < n) {
        power <<= 1;
    }
    return power;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:770,execs:324,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int result = smallest_power_of_two(n);
    printf("The smallest power of 2 greater than or equal to %d is %d\n", n, result);
    return 0;
}
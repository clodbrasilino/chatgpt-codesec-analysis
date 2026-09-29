#include <stdio.h>
#include <stdbool.h>

int highest_power_of_2_less_than_n(int n) {
    int power = 1;
    while (power * 2 <= n) {
        power *= 2;
    }
    return power;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:1316,execs:567,op:havoc,rep:5; likely memory-safety defect
  */

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    
    if (n > 0) {
        int result = highest_power_of_2_less_than_n(n);
        printf("The highest power of 2 less than or equal to %d is %d\n", n, result);
    } else {
        printf("Please enter a positive number.\n");
    }
    return 0;
}
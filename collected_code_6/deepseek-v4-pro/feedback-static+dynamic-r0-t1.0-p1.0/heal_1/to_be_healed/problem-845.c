#include <stdio.h>
#include <math.h>

int count_factorial_digits(int n) {
    if (n < 0) {
        return -1;
    }
    if (n <= 1) {
        return 1;
    }
    
    double digits = 0.0;
    for (int i = 2; i <= n; i++) {
        digits += log10(i);
    }
    
    return (int)floor(digits) + 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:4847,execs:310,op:havoc,rep:11; likely memory-safety defect
  */

int main(void) {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = count_factorial_digits(n);
    if (result == -1) {
        printf("Factorial is not defined for negative numbers\n");
    } else {
        printf("Number of digits in %d! is %d\n", n, result);
    }
    
    return 0;
}
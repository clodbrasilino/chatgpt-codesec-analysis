#include <stdio.h>

int sum_positive_series(int n) {
    int sum = 0;
    
    if (n <= 0) {
        return 0;
    }
    
    for (int i = n; i > 0; i -= 2) {
        sum += i;
    }
    
    return sum;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000003,time:726,execs:363,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    int n;
    
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    int result = sum_positive_series(n);
    printf("Sum: %d\n", result);
    
    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_difference_of_squares(long long n) {
    if (n < 0) {
        n = -n;
    }
    return n % 4 != 2;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:59862,execs:24585,op:havoc,rep:1; likely memory-safety defect
  */

int main(void) {
    long long num;
    int scan_result;
    
    printf("Enter a number: ");
    scan_result = scanf("%lld", &num);
    
    if (scan_result != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (is_difference_of_squares(num)) {
        printf("%lld can be represented as difference of two squares\n", num);
    } else {
        printf("%lld cannot be represented as difference of two squares\n", num);
    }
    
    return 0;
}
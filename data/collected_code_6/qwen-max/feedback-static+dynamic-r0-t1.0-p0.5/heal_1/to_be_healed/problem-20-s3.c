#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_woodall_number(long n) {
    if (n < 1) return false;
    for (long k = 1; ; k++) {
        long woodall = k * pow(2, k) - 1;
        if (woodall == n) return true;
        if (woodall > n) return false;
    }
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:1552,execs:972,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    long number;
    printf("Enter a number: ");
    scanf("%ld", &number);
    if (is_woodall_number(number)) {
        printf("%ld is a Woodall number.\n", number);
    } else {
        printf("%ld is not a Woodall number.\n", number);
    }
    return 0;
}
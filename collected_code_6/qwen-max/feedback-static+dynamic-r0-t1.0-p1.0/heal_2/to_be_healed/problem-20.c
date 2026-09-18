#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

bool is_woodall_number(unsigned long long n) {
    if (n == 0) return false;
    for (unsigned long long k = 1; (k << k) <= n && k < ULLONG_MAX / 2; ++k) {
        if ((k << k) - k == n) {
            return true;
        }
    }
    return false;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:291,execs:135,op:havoc,rep:4; likely memory-safety defect
  */

int main() {
    unsigned long long num;
    printf("Enter a number: ");
    if (scanf("%llu", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    if (is_woodall_number(num)) {
        printf("%llu is a Woodall number.\n", num);
    } else {
        printf("%llu is not a Woodall number.\n", num);
    }
    return 0;
}
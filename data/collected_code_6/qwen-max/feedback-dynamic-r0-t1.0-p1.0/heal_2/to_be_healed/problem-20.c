#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdint.h>

bool is_woodall_number(uint64_t n) {
    if (n == 0) return false;
    for (uint64_t k = 1; (k << k) <= n; ++k) {
        uint64_t candidate = (k << k) - k;
        if (candidate == n) {
            return true;
        }
    }
    return false;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000004,time:971,execs:660,op:havoc,rep:8; likely memory-safety defect
  */

int main() {
    uint64_t num;
    printf("Enter a number: ");
    if (scanf("%llu", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (is_woodall_number(num)) {
        printf("%llu is a Woodall number.\n", num);
    } else {
        printf("%llu is not a Woodall number.\n", num);
    }
    return 0;
}
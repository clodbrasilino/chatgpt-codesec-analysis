#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

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
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:28054,execs:35,op:havoc,rep:5; likely memory-safety defect
  */

int main() {
    uint64_t num;
    printf("Enter a number: ");
    while (scanf("%" SCNu64, &num) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. Please enter a number: ");
    }
    if (is_woodall_number(num)) {
        printf("%" PRIu64 " is a Woodall number.\n", num);
    } else {
        printf("%" PRIu64 " is not a Woodall number.\n", num);
    }
    return 0;
}
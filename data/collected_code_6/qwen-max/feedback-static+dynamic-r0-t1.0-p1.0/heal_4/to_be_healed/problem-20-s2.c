#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

bool is_woodall(uint64_t n) {
    for (uint64_t k = 1; ; ++k) {
        uint64_t woodall_number = k * (1ULL << k) - 1;
        if (woodall_number == n) return true;
        if (woodall_number > n) break;
    }
    return false;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:474,execs:237,op:havoc,rep:5; likely memory-safety defect
  */

int main() {
    uint64_t number;
    printf("Enter a number: ");
    scanf("%lu", &number);

    if (is_woodall(number)) {
        printf("%lu is a Woodall number.\n", number);
    } else {
        printf("%lu is not a Woodall number.\n", number);
    }

    return 0;
}
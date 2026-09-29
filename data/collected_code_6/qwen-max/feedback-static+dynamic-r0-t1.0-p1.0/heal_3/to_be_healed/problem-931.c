#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

bool is_valid_input(const char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') return false;
        str++;
    }
    return true;
}

long long sum_of_cubes(long long n) {
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 + 1 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000006,time:40262,execs:11754,op:havoc,rep:40)
     * UBSan: signed integer overflow: 6666666666666666666 * 6666666666666666667 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:1975,execs:563,op:havoc,rep:2)
     * UBSan: signed integer overflow: -4611686018427387904 * -4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000006,time:40262,execs:11754,op:havoc,rep:40)
     * UBSan: signed integer overflow: 1091282575167877575 * 1091282575167877575 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000005,time:1975,execs:563,op:havoc,rep:2)
     * UBSan: signed integer overflow: 9223372036854775807 * -9223372036854775808 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000006,time:40262,execs:11754,op:havoc,rep:40)
     */
    long long result = (n * (n + 1) / 2) * (n * (n + 1) / 2);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000005,time:1483,execs:449,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[20];
    printf("Enter a positive integer: ");
    if (fgets(input, sizeof(input), stdin) == NULL || !is_valid_input(input)) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long n = strtoll(input, NULL, 10);
    if (n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    printf("The sum of the cubes of the first %lld natural numbers is: %lld\n", n, result);
    return 0;
}
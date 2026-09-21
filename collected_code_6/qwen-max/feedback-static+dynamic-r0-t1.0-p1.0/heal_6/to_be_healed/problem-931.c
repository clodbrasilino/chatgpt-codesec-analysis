#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

bool is_valid_input(const char *str) {
    while (*str) {
        if (*str < '0' || *str > '9') return false;
        str++;
    }
    return true;
}

long long sum_of_cubes(long long n) {
    if (n <= 0 || n > (LLONG_MAX / 2)) {
        return -1;
    }
    long long temp = (n * (n + 1) / 2);
    if (temp > (LLONG_MAX / temp)) {
        return -1;
    }
    long long result = temp * temp;
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000006,time:2716,execs:835,op:havoc,rep:1; likely memory-safety defect
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
    input[strcspn(input, "\n")] = 0;
    long long n = strtoll(input, NULL, 10);
    if (n < 1 || n > LLONG_MAX) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    if (result == -1) {
        printf("Calculation overflowed. Result is too large.\n");
        return 1;
    }
    printf("The sum of the cubes of the first %lld natural numbers is: %lld\n", n, result);
    return 0;
}
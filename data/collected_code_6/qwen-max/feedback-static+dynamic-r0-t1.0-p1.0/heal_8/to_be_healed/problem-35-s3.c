#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdlib.h>

int64_t nth_rectangular_number(int64_t n) {
    if (n > INT64_MAX / (n + 1)) {
        fprintf(stderr, "Overflow detected\n");
        return -1;
    }
    int64_t result = n * (n + 1);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:6924,execs:1915,op:havoc,rep:2; likely memory-safety defect
  */

int main() {
    int64_t n;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[20];

    printf("Enter the value of n: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    char *endptr;
    n = strtoll(input, &endptr, 10);

    if (*endptr != '\n' && *endptr != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (n < 1) {
        fprintf(stderr, "n must be a positive integer\n");
        return 1;
    }

    int64_t result = nth_rectangular_number(n);
    if (result == -1) {
        return 1;
    }

    printf("The %" PRId64 "-th rectangular number is: %" PRId64 "\n", n, result);
    return 0;
}
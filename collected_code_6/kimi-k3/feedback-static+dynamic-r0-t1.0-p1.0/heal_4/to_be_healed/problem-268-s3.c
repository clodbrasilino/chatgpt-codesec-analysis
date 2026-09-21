#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long star_number(unsigned int n) {
    /* Possible weaknesses found:
     *  Assuming that condition 'n==0' is not redundant
     */
    if (n == 0) {
        return 0;
    }
    /* Possible weaknesses found:
     *  Condition 'n>0' is always true
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     */
    if (n > 0 && (unsigned long long)n > (ULLONG_MAX - 1) / 6 / (n - 1)) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 7999999998 * 1333333332 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000007,time:5808,execs:1676,op:havoc,rep:1)
     * UBSan: signed integer overflow: 8005999998 * 1334333332 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:31019,execs:9182,op:havoc,rep:10)
     */
    return 6LL * n * (n - 1) + 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:668,execs:209,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    long val;
    unsigned int n;
    long long result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);

    if (errno == ERANGE || val < 0 || val > UINT_MAX) {
        fprintf(stderr, "Invalid input: out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input: not a valid integer\n");
        return EXIT_FAILURE;
    }

    n = (unsigned int)val;

    result = star_number(n);
    if (result == -1) {
        fprintf(stderr, "Input too large: would cause overflow\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}
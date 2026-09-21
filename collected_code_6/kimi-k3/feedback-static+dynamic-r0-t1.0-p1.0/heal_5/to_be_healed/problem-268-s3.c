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
     *  Either the condition 'n>0' is redundant or there is division by zero at line 10. [zerodivcond]
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     *  Division by zero
     *  Assuming that condition 'n>0' is not redundant
     */
    if (n > 0 && (unsigned long long)n > ((unsigned long long)LLONG_MAX - 1) / 6 / (n - 1)) {
        return -1;
    }
    return 6LL * n * (n - 1) + 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:399,execs:163,op:havoc,rep:4; likely memory-safety defect
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
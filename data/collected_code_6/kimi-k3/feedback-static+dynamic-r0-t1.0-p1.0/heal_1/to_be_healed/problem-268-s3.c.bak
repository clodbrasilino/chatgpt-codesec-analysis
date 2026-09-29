#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long star_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9666666666 * 1611111110 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000007,time:3196,execs:1421,op:havoc,rep:1)
     */
    return 6LL * n * (n - 1) + 1;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:409,execs:211,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
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

    /* Possible weaknesses found:
     * UBSan: division by zero (AFL crash: id:000002,sig:06,src:000006,time:7288,execs:3155,op:havoc,rep:7)
     * ASan: FPE (AFL crash: id:000002,sig:06,src:000006,time:7288,execs:3155,op:havoc,rep:7)
     */
    if (n > 0 && n > (ULLONG_MAX - 1) / 6 / (n - 1)) {
        fprintf(stderr, "Input too large: would cause overflow\n");
        return EXIT_FAILURE;
    }

    result = star_number(n);
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}
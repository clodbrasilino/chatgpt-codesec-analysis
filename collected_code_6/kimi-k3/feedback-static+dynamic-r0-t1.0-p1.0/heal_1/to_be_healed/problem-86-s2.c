#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 7, got <no output>
  *  test case 0 failed: expected 271, got <no output>
  *  test case 2 failed: expected 217, got <no output>
  */

long long centered_hexagonal(int n) {
    if (n < 1) {
        return -1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 49381827065729284 * 222220222 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:20250,execs:9001,op:havoc,rep:4)
     * UBSan: signed integer overflow: 49381826621288841 * 222220221 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000006,time:20250,execs:9001,op:havoc,rep:4)
     */
    return (long long)n * n * n - (long long)(n - 1) * (n - 1) * (n - 1);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000002,time:484,execs:263,op:havoc,rep:2; likely memory-safety defect
  */

int main(void) {
    char input[32];
    char *endptr;
    long val;
    int n;
    long long result;

    if (fgets(input, sizeof(input), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(input, &endptr, 10);
    
    if (errno != 0 || endptr == input || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (val < 1 || val > INT_MAX) {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }

    n = (int)val;
    result = centered_hexagonal(n);
    
    if (result < 0) {
        fprintf(stderr, "Calculation error\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}
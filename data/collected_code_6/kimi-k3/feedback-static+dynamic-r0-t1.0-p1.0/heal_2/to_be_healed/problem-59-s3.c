#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>

int64_t octagonal_number(int64_t n) {
    if (n > 3037000499LL) {
        errno = ERANGE;
        return -1;
    }
    return n * (3 * n - 2);
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:56449,execs:19128,op:havoc,rep:28; likely memory-safety defect
  */

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[64];
    char *endptr;
    int64_t n;
    int64_t result;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    n = strtoimax(buffer, &endptr, 10);
    
    if (errno == ERANGE || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    if (n < 0) {
        fprintf(stderr, "Input must be non-negative\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    result = octagonal_number(n);
    if (errno == ERANGE) {
        fprintf(stderr, "Input too large: integer overflow\n");
        return EXIT_FAILURE;
    }
    
    printf("%" PRId64 "\n", result);
    
    return EXIT_SUCCESS;
}
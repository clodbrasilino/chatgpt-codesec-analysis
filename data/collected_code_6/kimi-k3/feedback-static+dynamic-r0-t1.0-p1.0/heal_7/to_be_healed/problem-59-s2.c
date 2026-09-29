#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int64_t octagonal_number(int64_t n) {
    if (n < 0 || n > 3037000499LL) {
        return -1;
    }
    return n * (3 * n - 2);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr;
    int64_t n;
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    
    if (strchr(buffer, '\n') == NULL) {
        int c;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((c = getchar()) != '\n' && c != EOF);
        return 1;
    }
    
    errno = 0;
    n = strtoimax(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return 1;
    }
    
    int64_t result = octagonal_number(n);
    if (result == -1) {
        return 1;
    }
    
    printf("%" PRId64 "\n", result);
    return 0;
}
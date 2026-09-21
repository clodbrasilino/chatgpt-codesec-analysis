#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>

#define MAX_N 91

int64_t perrin(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    
    int64_t a = 3, b = 0, c = 2;
    int64_t result = 0;
    
    for (int i = 3; i <= n; i++) {
        if (a > 0 && b > INT64_MAX - a) {
            return INT64_MAX;
        }
        if (a < 0 && b < INT64_MIN - a) {
            return INT64_MIN;
        }
        result = a + b;
        a = b;
        b = c;
        c = result;
    }
    
    return result;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    long n;
    char *endptr;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }

    if (n < 0 || n > MAX_N) {
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", perrin((int)n));
    return EXIT_SUCCESS;
}
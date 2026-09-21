#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long perrin(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    
    long long a = 3, b = 0, c = 2;
    long long result = 0;
    
    for (int i = 3; i <= n; i++) {
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
    char *endptr;
    long long_input;
    int n;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    long_input = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        return EXIT_FAILURE;
    }
    
    if (long_input < 0 || long_input > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    n = (int)long_input;

    printf("%lld\n", perrin(n));
    return EXIT_SUCCESS;
}
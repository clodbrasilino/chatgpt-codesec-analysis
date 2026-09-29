#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

long long perrin(int n) {
    if (n == 0) return 3;
    if (n == 1) return 0;
    if (n == 2) return 2;
    
    long long prev3 = 3;
    long long prev2 = 0;
    long long prev1 = 2;
    long long result = 0;
    
    for (int i = 3; i <= n; i++) {
        result = prev2 + prev3;
        prev3 = prev2;
        prev2 = prev1;
        prev1 = result;
    }
    
    return result;
}

int main(void) {
    int n;
    char buffer[256];
    char *endptr;
    long val;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    val = strtol(buffer, &endptr, 10);
    
    if (errno != 0 || endptr == buffer || *endptr != '\n' && *endptr != '\0') {
        return EXIT_FAILURE;
    }
    
    if (val < 0 || val > 90) {
        return EXIT_FAILURE;
    }
    
    n = (int)val;
    printf("%lld\n", perrin(n));
    return EXIT_SUCCESS;
}
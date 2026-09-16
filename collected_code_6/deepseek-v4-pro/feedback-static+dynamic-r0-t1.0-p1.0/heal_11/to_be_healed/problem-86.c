#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long centered_hexagonal(int n) {
    if (n < 1) {
        return -1;
    }
    return 3LL * n * (n - 1) + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int n;
    char *endptr;
    long val;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }
    
    errno = 0;
    val = strtol(argv[1], &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || val > INT_MAX || val < INT_MIN) {
        printf("Invalid input\n");
        return 1;
    }
    
    n = (int)val;
    
    long long result = centered_hexagonal(n);
    
    if (result < 0) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("%lld\n", result);
    return 0;
}
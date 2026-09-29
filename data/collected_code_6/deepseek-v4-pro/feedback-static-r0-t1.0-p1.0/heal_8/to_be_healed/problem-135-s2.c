#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long hexagonal_number(int n) {
    if (n <= 0 || n > (INT_MAX / 2)) {
        errno = EINVAL;
        return -1;
    }
    
    long long result = (long long)n * (2LL * n - 1);
    
    if (result < 0) {
        errno = ERANGE;
        return -1;
    }
    
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }
    
    char *endptr;
    errno = 0;
    long input = strtol(argv[1], &endptr, 10);
    
    if (errno != 0 || *endptr != '\0' || endptr == argv[1]) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (input <= 0 || input > INT_MAX) {
        fprintf(stderr, "Input out of range\n");
        return 1;
    }
    
    int n = (int)input;
    errno = 0;
    long long result = hexagonal_number(n);
    
    if (errno != 0) {
        fprintf(stderr, "Error calculating hexagonal number\n");
        return 1;
    }
    
    printf("%lld\n", result);
    return 0;
}
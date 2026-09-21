#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int is_scalene(long a, long b, long c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    if (a != b && b != c && a != c) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long a = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || a < INT_MIN || a > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    long b = strtol(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || b < INT_MIN || b > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    errno = 0;
    long c = strtol(argv[3], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || c < INT_MIN || c > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    if (is_scalene(a, b, c)) {
        printf("Scalene\n");
    } else {
        printf("Not Scalene\n");
    }
    
    return EXIT_SUCCESS;
}
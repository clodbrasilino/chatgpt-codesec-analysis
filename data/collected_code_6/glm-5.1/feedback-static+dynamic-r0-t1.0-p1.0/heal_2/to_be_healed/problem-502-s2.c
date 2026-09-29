#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int find_remainder(int dividend, int divisor) {
    if (divisor == 0) {
        exit(EXIT_FAILURE);
    }
    return dividend % divisor;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int a = 10;
    int b = 3;
    
    if (argc == 3) {
        char *endptr1;
        errno = 0;
        long val1 = strtol(argv[1], &endptr1, 10);
        if (errno != 0 || endptr1 == argv[1] || val1 < INT_MIN || val1 > INT_MAX) {
            exit(EXIT_FAILURE);
        }
        a = (int)val1;

        char *endptr2;
        errno = 0;
        long val2 = strtol(argv[2], &endptr2, 10);
        if (errno != 0 || endptr2 == argv[2] || val2 < INT_MIN || val2 > INT_MAX) {
            exit(EXIT_FAILURE);
        }
        b = (int)val2;
    }
    
    int result = find_remainder(a, b);
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}
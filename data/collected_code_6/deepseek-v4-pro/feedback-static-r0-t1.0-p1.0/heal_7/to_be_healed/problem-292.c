#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int divide(int dividend, int divisor, int *result) {
    if (divisor == 0) {
        errno = EINVAL;
        return -1;
    }
    
    if (dividend == INT_MIN && divisor == -1) {
        errno = ERANGE;
        return -1;
    }
    
    *result = dividend / divisor;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <dividend> <divisor>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr1, *endptr2;
    long dividend = strtol(argv[1], &endptr1, 10);
    long divisor = strtol(argv[2], &endptr2, 10);
    
    if (endptr1 == argv[1] || *endptr1 != '\0' || 
        endptr2 == argv[2] || *endptr2 != '\0') {
        fprintf(stderr, "Error: Invalid numeric input\n");
        return EXIT_FAILURE;
    }
    
    if (dividend > INT_MAX || dividend < INT_MIN || 
        divisor > INT_MAX || divisor < INT_MIN) {
        fprintf(stderr, "Error: Input out of range\n");
        return EXIT_FAILURE;
    }
    
    int result;
    int status = divide((int)dividend, (int)divisor, &result);
    
    if (status != 0) {
        if (errno == EINVAL) {
            fprintf(stderr, "Error: Division by zero\n");
        } else if (errno == ERANGE) {
            fprintf(stderr, "Error: Result overflow\n");
        }
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
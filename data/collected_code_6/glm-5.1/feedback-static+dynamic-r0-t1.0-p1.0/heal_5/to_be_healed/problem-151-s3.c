#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int are_coprime(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }
    return gcd(a, b) == 1;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char * const argv[const]) {
    long val;
    int a, b;
    char *endptr;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer> <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    if (strnlen(argv[1], 12) > 11) {
        fprintf(stderr, "Invalid first argument\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || endptr == argv[1] || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid first argument\n");
        return EXIT_FAILURE;
    }
    a = (int)val;
    
    if (strnlen(argv[2], 12) > 11) {
        fprintf(stderr, "Invalid second argument\n");
        return EXIT_FAILURE;
    }
    
    errno = 0;
    val = strtol(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || endptr == argv[2] || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid second argument\n");
        return EXIT_FAILURE;
    }
    b = (int)val;
    
    if (are_coprime(a, b)) {
        printf("%d and %d are coprime\n", a, b);
    } else {
        printf("%d and %d are not coprime\n", a, b);
    }
    
    return EXIT_SUCCESS;
}
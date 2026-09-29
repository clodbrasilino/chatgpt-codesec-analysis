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

int main(int argc, char * const * argv) {
    long val;
    int a, b;
    char *endptr;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer> <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    size_t len1 = strnlen(argv[1], 12);
    if (len1 > 11 || (len1 > 1 && argv[1][0] == '-')) {
        if (len1 > 11 || argv[1][0] != '-') {
            fprintf(stderr, "Invalid first argument\n");
            return EXIT_FAILURE;
        }
    }
    
    errno = 0;
    val = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || endptr == argv[1] || val < INT_MIN || val > INT_MAX) {
        fprintf(stderr, "Invalid first argument\n");
        return EXIT_FAILURE;
    }
    a = (int)val;
    
    size_t len2 = strnlen(argv[2], 12);
    if (len2 > 11 || (len2 > 1 && argv[2][0] == '-')) {
        if (len2 > 11 || argv[2][0] != '-') {
            fprintf(stderr, "Invalid second argument\n");
            return EXIT_FAILURE;
        }
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
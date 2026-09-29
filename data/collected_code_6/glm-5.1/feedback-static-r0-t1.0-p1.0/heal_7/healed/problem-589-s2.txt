#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

int is_perfect_square(long long n) {
    if (n < 0) {
        return 0;
    }
    long long root = (long long)round(sqrt((double)n));
    if (root * root == n) {
        return 1;
    }
    return 0;
}

void find_perfect_squares(long long a, long long b) {
    if (a > b) {
        long long temp = a;
        a = b;
        b = temp;
    }
    if (a < 0) {
        a = 0;
    }
    long long start = (long long)ceil(sqrt((double)a));
    long long end = (long long)floor(sqrt((double)b));
    for (long long i = start; i <= end; i++) {
        printf("%lld\n", i * i);
    }
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }
    
    long long num1, num2;
    char *endptr1;
    char *endptr2;
    
    errno = 0;
    num1 = strtoll(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || errno != 0) {
        fprintf(stderr, "Invalid first argument\n");
        return 1;
    }
    
    errno = 0;
    num2 = strtoll(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || errno != 0) {
        fprintf(stderr, "Invalid second argument\n");
        return 1;
    }
    
    find_perfect_squares(num1, num2);
    return 0;
}
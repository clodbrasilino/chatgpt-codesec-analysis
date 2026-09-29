#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int min_jumps(int d, int jmp) {
    if (jmp < 0) {
        jmp = -jmp;
    }
    if (jmp == 0) {
        if (d == 0) {
            return 0;
        } else {
            return -1;
        }
    }
    int steps = d / jmp;
    if (d % jmp == 0) {
        return steps;
    } else {
        return steps + 1 + 1;
    }
}

int main(int argc, char * const * const argv) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    
    char *endptr1;
    errno = 0;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (errno != 0 || endptr1 == argv[1] || *endptr1 != '\0' || val1 < INT_MIN || val1 > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    char *endptr2;
    errno = 0;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (errno != 0 || endptr2 == argv[2] || *endptr2 != '\0' || val2 < INT_MIN || val2 > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    int d = (int)val1;
    int jmp = (int)val2;
    
    int res = min_jumps(d, jmp);
    printf("%d\n", res);
    
    return EXIT_SUCCESS;
}
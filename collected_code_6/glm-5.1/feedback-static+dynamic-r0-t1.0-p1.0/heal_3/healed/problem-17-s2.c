#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int perimeter(int side) {
    if (side < 0) {
        return -1;
    }
    if (side > INT_MAX / 4) {
        return -2;
    }
    return 4 * side;
}

int main(int argc, char * const * const argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(argv[1], &endptr, 10);
    
    if (endptr == argv[1] || *endptr != '\0') {
        return EXIT_FAILURE;
    }
    
    if (errno == ERANGE || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    int side = (int)val;
    int result = perimeter(side);
    
    if (result < 0) {
        return EXIT_FAILURE;
    }
    
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
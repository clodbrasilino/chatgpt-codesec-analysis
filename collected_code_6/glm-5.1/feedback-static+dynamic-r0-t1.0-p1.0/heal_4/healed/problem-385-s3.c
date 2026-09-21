#include <stdio.h>
#include <stdlib.h>

unsigned long perrin(int n) {
    if (n == 0) {
        return 3;
    }
    if (n == 1) {
        return 0;
    }
    if (n == 2) {
        return 2;
    }
    return perrin(n - 2) + perrin(n - 3);
}

int main(int argc, char * const argv[static 2]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 35) {
        return EXIT_FAILURE;
    }
    
    int n = (int)val;
    unsigned long result = perrin(n);
    printf("%lu\n", result);
    
    return EXIT_SUCCESS;
}
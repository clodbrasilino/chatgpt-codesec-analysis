#include <stdio.h>
#include <stdlib.h>

unsigned long long find_rectangular_number(int n) {
    if (n < 1) {
        return 0;
    }
    
    return (unsigned long long)n * (n + 1);
}

int main(int argc, char * const * argv) {
    int n;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    
    if (n < 1) {
        return EXIT_FAILURE;
    }
    
    printf("%llu\n", find_rectangular_number(n));
    
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

int find_last_digit(int number) {
    int absolute = number < 0 ? -number : number;
    return absolute % 10;
}

int main(int argc, char * const * const argv) {
    int number;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%d", &number) != 1) {
        return EXIT_FAILURE;
    }
    
    int result = find_last_digit(number);
    
    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
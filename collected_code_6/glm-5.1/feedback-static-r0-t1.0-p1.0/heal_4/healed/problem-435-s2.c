#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_last_digit(int number) {
    int absolute = number < 0 ? -number : number;
    return absolute % 10;
}

int main(int argc, char * const argv[const]) {
    long long num;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    if (sscanf(argv[1], "%lld", &num) != 1) {
        return EXIT_FAILURE;
    }
    
    if (num < INT_MIN || num > INT_MAX) {
        return EXIT_FAILURE;
    }
    
    int number = (int)num;
    int result = find_last_digit(number);
    
    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
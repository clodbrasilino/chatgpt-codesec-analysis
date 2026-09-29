#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_last_digit(int number) {
    int absolute = number == INT_MIN ? INT_MAX : (number < 0 ? -number : number);
    return absolute % 10;
}

int main(int argc, char * const argv[const]) {
    int number;
    
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (endptr == argv[1] || *endptr != '\0' || val < INT_MIN || val > INT_MAX) {
        return EXIT_FAILURE;
    }
    number = (int)val;
    
    int result = find_last_digit(number);
    
    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
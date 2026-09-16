#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int round_to_multiple(int number, int multiple) {
    if (multiple == 0) {
        fprintf(stderr, "Error: multiple cannot be zero\n");
        exit(EXIT_FAILURE);
    }
    
    int abs_multiple = abs(multiple);
    int remainder = number % abs_multiple;
    
    if (remainder == 0) {
        return number;
    }
    
    int lower = number - remainder;
    int upper = lower + abs_multiple;
    
    int distance_lower = abs(number - lower);
    int distance_upper = abs(upper - number);
    
    if (distance_lower < distance_upper) {
        return lower;
    } else if (distance_upper < distance_lower) {
        return upper;
    } else {
        return (multiple > 0) ? upper : lower;
    }
}

int main(void) {
    int num = 17;
    int mult = 5;
    int result = round_to_multiple(num, mult);
    printf("%d rounded to nearest multiple of %d is %d\n", num, mult, result);
    
    num = 23;
    mult = 7;
    result = round_to_multiple(num, mult);
    printf("%d rounded to nearest multiple of %d is %d\n", num, mult, result);
    
    num = -13;
    mult = 4;
    result = round_to_multiple(num, mult);
    printf("%d rounded to nearest multiple of %d is %d\n", num, mult, result);
    
    return 0;
}
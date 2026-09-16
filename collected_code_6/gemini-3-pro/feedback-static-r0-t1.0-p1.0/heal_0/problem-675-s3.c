#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int add_with_range(int a, int b, int range_start, int range_end);

int add_with_range(int a, int b, int range_start, int range_end) {
    if ((b > 0 && a > INT_MAX - b) || (b < 0 && a < INT_MIN - b)) {
        fprintf(stderr, "Integer overflow detected\n");
        exit(EXIT_FAILURE);
    }
    
    int sum = a + b;
    
    if (sum >= range_start && sum <= range_end) {
        return 20;
    }
    
    return sum;
}

int main(void) {
    int val1 = 5;
    int val2 = 10;
    int range_min = 10;
    int range_max = 20;
    
    int result = add_with_range(val1, val2, range_min, range_max);
    
    if (printf("%d\n", result) < 0) {
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
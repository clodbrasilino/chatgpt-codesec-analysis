#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_perfect_square(int num) {
    int root = (int)sqrt((double)num);
    return (root * root == num);
}

int square_root_of_perfect_number(int num) {
    if (num < 0) {
        fprintf(stderr, "Error: negative input\n");
        exit(EXIT_FAILURE);
    }
    
    if (!is_perfect_square(num)) {
        fprintf(stderr, "Error: input is not a perfect square\n");
        exit(EXIT_FAILURE);
    }
    
    return (int)sqrt((double)num);
}

int main(void) {
    int test_values[] = {0, 1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; ++i) {
        int value = test_values[i];
        int result = square_root_of_perfect_number(value);
        printf("Square root of %d is %d\n", value, result);
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int sum_of_divisors(int num) {
    if (num <= 0) {
        return -1;
    }
    int sum = 1;
    if (num == 1) {
        return sum;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }
    return sum + num;
}

int compare_divisor_sums(int a, int b) {
    if (a <= 0 || b <= 0) {
        return -1;
    }
    int sum_a = sum_of_divisors(a);
    int sum_b = sum_of_divisors(b);
    if (sum_a == -1 || sum_b == -1) {
        return -1;
    }
    if (sum_a == sum_b) {
        return 1;
    }
    return 0;
}

int main(int argc, char * const * argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <integer_a> <integer_b>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    char *endptr_a;
    char *endptr_b;
    long val_a = strtol(argv[1], &endptr_a, 10);
    long val_b = strtol(argv[2], &endptr_b, 10);
    
    if (*endptr_a != '\0' || *endptr_b != '\0') {
        fprintf(stderr, "Error: Invalid integer input.\n");
        return EXIT_FAILURE;
    }
    
    if (val_a <= 0 || val_b <= 0 || val_a > 2147483647 || val_b > 2147483647) {
        fprintf(stderr, "Error: Inputs must be positive integers within int range.\n");
        return EXIT_FAILURE;
    }
    
    int a = (int)val_a;
    int b = (int)val_b;
    
    int result = compare_divisor_sums(a, b);
    
    if (result == -1) {
        fprintf(stderr, "Error: Computation failed due to invalid inputs.\n");
        return EXIT_FAILURE;
    }
    
    if (result == 1) {
        printf("Same\n");
    } else {
        printf("Not Same\n");
    }
    
    return EXIT_SUCCESS;
}
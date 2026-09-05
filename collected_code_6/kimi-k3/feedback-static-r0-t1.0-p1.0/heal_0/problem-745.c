#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool is_self_dividing(int num) {
    int original = num;
    while (num > 0) {
        int digit = num % 10;
        if (digit == 0 || original % digit != 0) {
            return false;
        }
        num /= 10;
    }
    return true;
}

void find_self_dividing_numbers(int lower, int upper) {
    if (lower > upper || lower < 1) {
        fprintf(stderr, "Invalid range: lower must be >= 1 and <= upper\n");
        return;
    }
    
    for (int i = lower; i <= upper; i++) {
        if (is_self_dividing(i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main(void) {
    int lower, upper;
    
    printf("Enter lower bound: ");
    if (scanf("%d", &lower) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter upper bound: ");
    if (scanf("%d", &upper) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    find_self_dividing_numbers(lower, upper);
    
    return EXIT_SUCCESS;
}
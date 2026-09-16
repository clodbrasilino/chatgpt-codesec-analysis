#include <stdio.h>
#include <stdlib.h>

long long find_square_root(long long number) {
    long long start = 1;
    long long end = 0;
    long long ans = 0;

    if (number < 0) {
        return -1;
    }
    
    if (number == 0 || number == 1) {
        return number;
    }
    
    end = number / 2;
    
    while (start <= end) {
        long long mid = start + (end - start) / 2;
        long long mid_sq = mid * mid;
        
        if (mid_sq == number) {
            return mid;
        }
        
        if (mid_sq < number) {
            start = mid + 1;
            ans = mid;
        } else {
            end = mid - 1;
        }
    }
    
    return ans;
}

int main(void) {
    long long inputs[] = {6, 28, 496, 8128};
    size_t num_inputs = sizeof(inputs) / sizeof(inputs[0]);
    size_t i = 0;
    
    for (i = 0; i < num_inputs; i++) {
        long long result = find_square_root(inputs[i]);
        if (result != -1) {
            printf("%lld\n", result);
        } else {
            fprintf(stderr, "Invalid input: %lld\n", inputs[i]);
            return EXIT_FAILURE;
        }
    }
    
    return EXIT_SUCCESS;
}
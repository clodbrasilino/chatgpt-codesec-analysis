#include <stdio.h>
#include <stdint.h>

uint64_t count_cubes(int64_t n, int64_t k, int *error_flag) {
    if (error_flag) {
        *error_flag = 0;
    }
    if (n <= 0 || k <= 0 || k > n) {
        return 0;
    }
    
    uint64_t positions = (uint64_t)(n - k + 1);
    
    if (positions > 2642245) {
        if (error_flag) {
            *error_flag = 1;
        }
        return 0;
    }
    
    return positions * positions * positions;
}

int main(void) {
    int64_t n = 5;
    int64_t k = 2;
    int error_flag = 0;
    
    uint64_t result = count_cubes(n, k, &error_flag);
    
    if (error_flag != 0) {
        printf("Error: Calculation resulted in integer overflow.\n");
        return 1;
    }
    
    printf("%llu\n", (unsigned long long)result);
    
    return 0;
}
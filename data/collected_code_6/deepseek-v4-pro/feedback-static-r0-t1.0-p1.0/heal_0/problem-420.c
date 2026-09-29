#include <stdio.h>
#include <stdlib.h>

unsigned long long cube_sum_first_n_even(int n) {
    if (n <= 0) {
        return 0ULL;
    }
    
    unsigned long long sum = 0ULL;
    for (int i = 1; i <= n; i++) {
        unsigned long long even_num = 2ULL * i;
        sum += even_num * even_num * even_num;
    }
    return sum;
}

int main(void) {
    int n;
    
    printf("Enter n: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    unsigned long long result = cube_sum_first_n_even(n);
    printf("Cube sum of first %d even natural numbers = %llu\n", n, result);
    
    return EXIT_SUCCESS;
}
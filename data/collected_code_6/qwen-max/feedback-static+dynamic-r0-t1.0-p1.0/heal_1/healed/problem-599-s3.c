#include <stdio.h>
#include <stdint.h>

void calculate_sum_and_average(uint32_t n, uint32_t *sum, float *average) {
    *sum = (n * (n + 1)) / 2;
    if (n > 0) {
        *average = (float)*sum / n;
    } else {
        *average = 0.0f;
    }
}

int main() {
    uint32_t n, sum;
    float average;

    printf("Enter a positive integer: ");
    if (scanf("%u", &n) != 1 || n == 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    calculate_sum_and_average(n, &sum, &average);
    
    printf("Sum of first %u natural numbers is %u\n", n, sum);
    printf("Average of first %u natural numbers is %.2f\n", n, average);

    return 0;
}
#include <stdio.h>

void calculate_sum_and_average(int n, int *sum, float *average) {
    *sum = (n * (n + 1)) / 2;
    *average = (float)*sum / n;
}

int main() {
    int n, sum;
    float average;

    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    calculate_sum_and_average(n, &sum, &average);
    
    printf("Sum of first %d natural numbers is %d\n", n, sum);
    printf("Average of first %d natural numbers is %.2f\n", n, average);

    return 0;
}
#include <stdio.h>

void calculate(int n, float* avg, int* sum) {
    *sum = n*(n+1)/2;
    *avg = (float)(*sum)/n;
}

int main() {
    int n, sum;
    float avg;
    printf("Enter the number for n: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Please enter a positive integer for n.\n");
        return 1;
    }
    calculate(n, &avg, &sum);
    printf("Sum: %d Average: %.2f\n", sum, avg);
    return 0;
} 
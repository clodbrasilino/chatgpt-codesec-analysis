#include<stdio.h>

double sum_inverse_divisors(int n) {
    double sum = 0;

    if(n <= 0) {
        printf("Input must be a positive integer. Exiting.\n");
        return -1;
    }

    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            sum += 1 / (double)i;
        }
    }

    return sum;
}

int main() {
    int num;
    double result;
    printf("Enter a number: ");
    scanf("%d", &num);

    result = sum_inverse_divisors(num);
    
    if(result != -1){
        printf("Sum of inverse of divisors of the number is : %.2f\n", result);
    }

    return 0;
}
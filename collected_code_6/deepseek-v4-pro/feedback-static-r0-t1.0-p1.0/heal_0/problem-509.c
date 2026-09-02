#include <stdio.h>

double average_of_odd_numbers(int n) {
    if (n <= 0 || n % 2 == 0) {
        return 0.0;
    }
    
    int count = (n + 1) / 2;
    long sum = (long)count * count;
    
    return (double)sum / count;
}

int main(void) {
    int n;
    
    printf("Enter an odd number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (n <= 0 || n % 2 == 0) {
        printf("Please enter a positive odd number\n");
        return 1;
    }
    
    double result = average_of_odd_numbers(n);
    printf("Average of odd numbers from 1 to %d: %.2f\n", n, result);
    
    return 0;
}
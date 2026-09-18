#include<stdio.h>

long long getNthRectangularNumber(int n) {
    if(n < 1)
        return -1;

    return (long long)n*(n+1);
}

int main() {
    int n;
    printf("Enter an integer: ");
    scanf("%d", &n);
    long long result = getNthRectangularNumber(n);
    if(result != -1) {
        printf("The %d-th rectangular number is %lld\n", n, result);
    } else {
        printf("Invalid input. Please enter a positive integer.\n");
    }
    return 0;
}
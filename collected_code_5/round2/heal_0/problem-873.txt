#include<stdio.h>

int fibonacci(int n) {
    if (n <= 0)
        return 0;
    else if (n == 1)
        return 1;
    else
        return(fibonacci(n-1) + fibonacci(n-2));
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (num < 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    else {
        printf("Fibonacci Sequence: %d\n", fibonacci(num));
        return 0;
    }
}
#include <stdio.h>

long long jacobsthalLucas(int n) {
    // base cases
    if (n == 0)  return 2;
    if (n == 1)  return 1;
    
    // recursive case
    return 2 * jacobsthalLucas(n - 1) + jacobsthalLucas(n - 2);
}

int main() {
    int n;
    
    printf("Enter a positive integer: ");
    scanf("%d", &n);
    
    if (n < 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    } 
    
    printf("The Jacobsthal-Lucas number at position %d is %lld\n", n, jacobsthalLucas(n));
    
    return 0;
}
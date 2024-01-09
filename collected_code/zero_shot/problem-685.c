#include <stdio.h>

int isPrime(int num) {
    if(num < 2) {
        return 0;
    }
    for(int i = 2; i <= num/2; i++) {
        if(num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int sumOfPrimes(int n) {
    int sum = 0;
    for(int i = 2; i <= n; i++) {
        if(isPrime(i)) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of prime numbers between 1 and %d = %d", n, sumOfPrimes(n));
    return 0;
}
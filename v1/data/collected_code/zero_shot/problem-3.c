#include <stdio.h>

// Function to check if a number is prime
int isPrime(int num) {
    int i;
    
    // Check if num is divisible by any number from 2 to num/2
    for (i = 2; i <= num / 2; i++) {
        if (num % i == 0) {
            return 0; // Not a prime number
        }
    }
    
    return 1; // Prime number
}

// Function to identify non-prime numbers
void identifyNonPrime(int start, int end) {
    int i;
    
    printf("Non-prime numbers between %d and %d are: ", start, end);
    
    // Iterate through the range start to end
    for (i = start; i <= end; i++) {
        if (!isPrime(i)) {
            printf("%d ", i);
        }
    }
    
    printf("\n");
}

int main() {
    int start, end;
    
    printf("Enter the range (start end): ");
    scanf("%d %d", &start, &end);
    
    identifyNonPrime(start, end);
    
    return 0;
}
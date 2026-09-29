#include <stdio.h>

int isPrime(int n);

int countPrimes(int num);

int main(void);

int isPrime(int n) {
    if (n <= 1) {
        return 0;
    }
    
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    
    return 1;
}

int countPrimes(int num) {
    int count = 0;
    
    for (int i = 2; i < num; i++) {
        if (isPrime(i)) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    int num = 0;
    printf("Enter a non-negative number: ");
    scanf("%d", &num);
    
    if(num < 0){
        printf("Number is negative. Please enter a non-negative number.");
        return 0;
    }
    
    int primeCount = countPrimes(num);
    
    printf("Number of prime numbers less than %d is %d\n", num, primeCount);
    
    return 0;
}
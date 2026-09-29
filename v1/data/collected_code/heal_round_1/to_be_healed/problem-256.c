#include <stdio.h>

int isPrime(int n);

int countPrimes(int num) {
    int count = 0;
    
    for (int i = 2; i < num; i++) {
        if (isPrime(i)) {
            count++;
        }
    }
    
    return count;
}

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

int main(void) {
    int num;
    printf("Enter a non-negative number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'num' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &num);
    
    int primeCount = countPrimes(num);
    
    printf("Number of prime numbers less than %d is %d\n", num, primeCount);
    
    return 0;
}
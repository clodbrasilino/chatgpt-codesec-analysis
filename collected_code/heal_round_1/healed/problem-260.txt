#include <stdio.h>

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

int countPrimes(int n) {
    int count = 0;
    int num = 1;

    while (count < n) {
        num++;
        if (isPrime(num) && isPrime((num - 1) / 2)) {
            count++;
        }
    }
    
    return num;
}

int main() {
    int n = 5;
    int result = countPrimes(n);
    
    printf("The %dth Newman–Shanks–Williams prime number is: %d\n", n, result);
    
    return 0;
}

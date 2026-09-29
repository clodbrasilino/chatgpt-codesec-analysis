#include <stdio.h>
#include <stdbool.h>

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

int countPrimes(int num) {
    int count = 0;
    for (int i = 2; i < num; i++) {
        if (isPrime(i)) count++;
    }
    return count;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Number of prime numbers less than %d is %d\n", num, countPrimes(num));
    return 0;
}
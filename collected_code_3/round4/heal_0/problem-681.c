#include <stdio.h>
#include <stdbool.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

int smallestPrimeDivisor(int n) {
    if (n <= 1) return -1;
    if (n % 2 == 0) return 2;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0 && isPrime(i)) return i;
    }
    return n;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int smallestPrime = smallestPrimeDivisor(num);
    if (smallestPrime == -1) {
        printf("Number should be greater than 1\n");
    } else {
        printf("Smallest prime divisor of %d is %d\n", num, smallestPrime);
    }
    return 0;
}
#include <stdio.h>
#include <stdbool.h>

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int sumPrimeDivisors(int n) {
    int sum = 0;
    for (int i = 2; i <= n; i++) {
        if (n % i == 0) {
            if (isPrime(i)) {
                sum += i;
            }
        }
    }
    return sum;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Sum of prime divisors: %d\n", sumPrimeDivisors(num));
    return 0;
}
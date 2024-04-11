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

int countDistinctPowers(int n) {
    int count = 0;
    for (int i = 2; i <= n; i++) {
        if (n % i == 0 && isPrime(i)) {
            while (n % i == 0) {
                n /= i;
                count++;
            }
        }
    }
    return count;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("Number of distinct powers of prime factors: %d\n", countDistinctPowers(num));
    return 0;
}
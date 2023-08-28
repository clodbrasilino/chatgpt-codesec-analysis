#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isPrime(int n) {
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    return true;
}

int distinctPowerOfPrimeFactor(int n) {
    int count = 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (isPrime(i)) {
            while (n % i == 0) {
                count++;
                n /= i;
            }
        }
    }
    if (n > 1)
        count++;
    return count;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    int result = distinctPowerOfPrimeFactor(num);
    printf("Number of distinct power of prime factors: %d\n", result);
    return 0;
}
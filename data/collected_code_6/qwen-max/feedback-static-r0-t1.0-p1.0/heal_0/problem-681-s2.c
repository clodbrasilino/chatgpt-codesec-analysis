#include <stdio.h>
#include <stdbool.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int smallest_prime_divisor(int n) {
    if (n <= 1) return -1;
    if (n % 2 == 0) return 2;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0 && is_prime(i)) return i;
    }
    return n;
}

int main() {
    int number = 13195;
    int result = smallest_prime_divisor(number);
    if (result != -1) {
        printf("The smallest prime divisor of %d is %d\n", number, result);
    } else {
        printf("No prime divisor found for %d\n", number);
    }
    return 0;
}
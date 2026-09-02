#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int smallest_prime_divisor(int n) {
    if (n <= 1) return -1;
    if (n % 2 == 0) return 2;
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0 && is_prime(i)) return i;
    }
    if (is_prime(n)) return n;
    return -1;
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int result = smallest_prime_divisor(num);
    if (result != -1) {
        printf("Smallest prime divisor of %d is %d\n", num, result);
    } else {
        printf("No prime divisor found for %d\n", num);
    }
    return 0;
}
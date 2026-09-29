#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool is_prime(long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

long ns_williams_prime(int n) {
    long a = 1, b = 1;
    int count = 0;
    while (true) {
        long next = 2 * b + a;
        a = b;
        b = next;
        if (is_prime(next)) {
            count++;
            if (count == n) return next;
        }
    }
}

int main() {
    int n;
    printf("Enter the nth Newman–Shanks–Williams prime number to find: ");
    scanf("%d", &n);
    if (n > 0) {
        long result = ns_williams_prime(n);
        printf("The %dth Newman–Shanks–Williams prime number is: %ld\n", n, result);
    } else {
        printf("Please enter a positive integer.\n");
    }
    return 0;
}
#include <stdio.h>

long centered_hexagonal_number(long n) {
    return 3 * n * (n - 1) + 1;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        return 1;
    }
    long result = centered_hexagonal_number(n);
    printf("The %ldth centered hexagonal number is: %ld\n", n, result);
    return 0;
}
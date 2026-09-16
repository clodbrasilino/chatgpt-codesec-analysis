#include <stdio.h>
#include <math.h>

long long next_perfect_square(long long n) {
    long long root = sqrt(n);
    if (root * root == n) {
        return (root + 1) * (root + 1);
    } else {
        return (root + 1) * (root + 1);
    }
}

int main() {
    long long number;
    printf("Enter a number: ");
    scanf("%lld", &number);
    long long result = next_perfect_square(number);
    printf("The next perfect square is: %lld\n", result);
    return 0;
}
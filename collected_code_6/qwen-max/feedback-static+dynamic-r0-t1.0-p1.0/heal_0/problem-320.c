#include <stdio.h>

long long square_sum(long long n) {
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
}

long long sum_of_squares(long long n) {
    return n * (n + 1) * (2 * n + 1) / 6;
}

long long difference_between_sums(long long n) {
    return square_sum(n) - sum_of_squares(n);
}

int main() {
    long long n;
    printf("Enter a number: ");
    if (scanf("%lld", &n) != 1) {
        return 1;
    }
    printf("Difference: %lld\n", difference_between_sums(n));
    return 0;
}
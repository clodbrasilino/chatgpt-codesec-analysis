#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>

long long sum_of_cubes(long n) {
    if (n > 0 && (unsigned long long)n * n * n > ULLONG_MAX / (n * n)) return 0;
    unsigned long long result = (unsigned long long)n * (n + 1) / 2;
    if (result * result > ULLONG_MAX) return 0;
    return (long long)(result * result);
}

long long sum_of_numbers(long n) {
    if (n > 0 && (unsigned long long)n * (n + 1) > ULLONG_MAX / 2) return 0;
    unsigned long long result = (unsigned long long)n * (n + 1) / 2;
    return (long long)result;
}

long long difference(long n) {
    long long cubes = sum_of_cubes(n);
    long long numbers = sum_of_numbers(n);
    if (cubes < 0 || numbers < 0) return 0;
    return cubes - numbers;
}

int main() {
    long n;
    printf("Enter a natural number: ");
    if (scanf("%ld", &n) != 1 || n < 1) {
        printf("Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}
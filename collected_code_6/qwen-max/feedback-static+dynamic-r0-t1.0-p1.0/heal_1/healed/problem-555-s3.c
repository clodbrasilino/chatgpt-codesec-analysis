#include <stdio.h>
#include <stdint.h>

long long sum_of_cubes(long n) {
    long long result = (n * (n + 1) / 2);
    return result * result;
}

long long sum_of_numbers(long n) {
    return (n * (n + 1)) / 2;
}

long long difference(long n) {
    return sum_of_cubes(n) - sum_of_numbers(n);
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
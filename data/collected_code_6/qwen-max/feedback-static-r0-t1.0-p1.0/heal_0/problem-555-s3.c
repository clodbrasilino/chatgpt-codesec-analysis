#include <stdio.h>

long long sum_of_cubes(long n) {
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
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
    scanf("%ld", &n);

    if (n < 1) {
        printf("Please enter a valid natural number.\n");
        return 1;
    }

    long long diff = difference(n);
    printf("The difference is: %lld\n", diff);
    return 0;
}
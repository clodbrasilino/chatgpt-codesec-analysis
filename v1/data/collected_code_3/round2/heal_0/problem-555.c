#include <stdio.h>

long long int sumOfCubes(int n) {
    long long int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += i * i * i;
    }
    return sum;
}

long long int sumOfNumbers(int n) {
    return n * (n + 1) / 2;
}

long long int difference(int n) {
    return sumOfCubes(n) - sumOfNumbers(n);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The difference is: %lld\n", difference(n));
    return 0;
}
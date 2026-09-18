#include <stdio.h>

long long cubeSum(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += (long long)i * i * i;
    }
    return sum;
}

int main() {
    int n;
    printf("\nEnter the number: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("\nInvalid input. The number should be a positive integer.\n");
        return -1;
    }

    long long result = cubeSum(n);
    printf("\nCube sum of first %d natural numbers is: %lld\n", n, result);

    return 0;
}
#include <stdio.h>

long long sumOfCubes(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        int oddNumber = 2*i - 1;
        sum += oddNumber * oddNumber * oddNumber;
    }
    return sum;
}

int main(void) {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Please, enter a positive number\n");
        return 1;
    }

    printf("Cubic sum: %lld\n", sumOfCubes(n));
    return 0;
}
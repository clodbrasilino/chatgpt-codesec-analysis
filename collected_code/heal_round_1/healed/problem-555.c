#include <stdio.h>

int difference(int n) {
    int sumOfCubes = 0;
    int sumOfNumbers = 0;

    for (int i = 1; i <= n; i++) {
        sumOfCubes += i * i * i;
        sumOfNumbers += i;
    }

    return sumOfCubes - sumOfNumbers;
}

int main() {
    int n = 0;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    int result = difference(n);
    printf("The difference is: %d\n", result);

    return 0;
}
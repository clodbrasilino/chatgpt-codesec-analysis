#include<stdio.h>

long long nthHexagonalNumber(int n) {
    if (n <= 0) {
        return 0;
    }
    return n * (2*n - 1);
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if(n < 0) {
        printf("Invalid input! Please enter a positive number.\n");
        return 0;
    }
    printf("%lld\n", nthHexagonalNumber(n));
    return 0;
}
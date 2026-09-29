#include <stdio.h>
#include <stdlib.h>

long long findNthHexagonalNumber(int n) {
    if(n<1) {
        printf("Error: Invalid input. The input number should be greater than 0.");
        exit(1);
    }
    return n*(2*n-1);
}

int main() {
    int n;
    printf("Enter the nth number: ");
    scanf("%d", &n);
    long long hexagonalNumber = findNthHexagonalNumber(n);
    printf("The %dth hexagonal number is: %lld\n", n, hexagonalNumber);
    return 0;
}
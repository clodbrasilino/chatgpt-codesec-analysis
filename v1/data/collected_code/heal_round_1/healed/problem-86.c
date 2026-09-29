#include <stdio.h>

int centeredHexagonalNumber(int n) {
    if (n == 1) {
        return 1;
    } else {
        return (3 * n * n - 3 * n + 1) + centeredHexagonalNumber(n - 1);
    }
}

int main() {
    int n = 0;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Number must be greater than 0");
        return -1;
    }

    int centeredHexNum = centeredHexagonalNumber(n);
    printf("The %dth centered hexagonal number is %d\n", n, centeredHexNum);

    return 0;
}
#include <stdio.h>

int centeredHexagonalNumber(int n) {
    if (n == 1) {
        return 1;
    } else {
        return (3 * n * n - 3 * n + 1) + centeredHexagonalNumber(n - 1);
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'n' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &n);

    int centeredHexNum = centeredHexagonalNumber(n);
    printf("The %dth centered hexagonal number is %d\n", n, centeredHexNum);

    return 0;
}
#include <stdio.h>
#include <math.h>

int checkSumOfSquares(int n) {
    for (int i = 0; i * i <= n; ++i) {
        for (int j = 0; j * j <= n; ++j) {
            if (i * i + j * j == n) {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (checkSumOfSquares(num)) {
        printf("Yes, the number can be represented as the sum of two squares.\n");
    } else {
        printf("No, the number cannot be represented as the sum of two squares.\n");
    }
    return 0;
}
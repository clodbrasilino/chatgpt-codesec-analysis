#include <stdio.h>
#include <math.h>

int checkSumOfSquares(int n) {
    int limit = sqrt(n);
    for (int i = 0; i <= limit; i++) {
        for (int j = 0; j <= limit; j++) {
            if ((i * i + j * j) == n) {
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
        printf("The number can be represented as the sum of two squares.\n");
    } else {
        printf("The number cannot be represented as the sum of two squares.\n");
    }
    return 0;
}
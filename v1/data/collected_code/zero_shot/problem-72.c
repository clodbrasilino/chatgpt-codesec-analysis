#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isDifferenceOfSquares(int num) {
    for (int i = 1; i * i <= num; i++) {
        int diff = num - i * i;
        int sqrtDiff = sqrt(diff);
        if (sqrtDiff * sqrtDiff == diff) {
            return true;
        }
    }
    return false;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (isDifferenceOfSquares(number)) {
        printf("%d can be represented as difference of two squares.", number);
    } else {
        printf("%d cannot be represented as difference of two squares.", number);
    }

    return 0;
}
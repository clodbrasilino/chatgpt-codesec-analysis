#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isDifferenceOfSquares(int num) {
    /* Possible weaknesses found:
     *  Assignment 'i=1', assigned value is 1
     */
    for (int i = 1; i * i <= num; i++) {
        /* Possible weaknesses found:
         *  diff is assigned 'num-i*i' here.
         */
        int diff = num - i * i;
        /* Possible weaknesses found:
         *  Invalid argument
         */
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
    /* Possible weaknesses found:
     *  Cannot determine that 'number' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number);

    if (isDifferenceOfSquares(number)) {
        printf("%d can be represented as difference of two squares.", number);
    } else {
        printf("%d cannot be represented as difference of two squares.", number);
    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

bool isDifferenceOfSquares(int num) {
    /* Possible weaknesses found:
     *  Assignment 'i=0', assigned value is 0
     */
    for (int i = 0; i * i <= num; ++i) {
        /* Possible weaknesses found:
         *  diff is assigned 'num-i*i' here.
         */
        int diff = num - i * i;
        /* Possible weaknesses found:
         *  Invalid argument
         */
        int sqrtDiff = (int)sqrt((double)diff);
        if (sqrtDiff * sqrtDiff == diff) {
            return true;
        }
    }
    return false;
}

int main() {
    int number = 0;
    printf("Enter a number: ");
    scanf("%d", &number);

    if (isDifferenceOfSquares(number)) {
        printf("%d can be represented as difference of two squares.\n", number);
    } else {
        printf("%d cannot be represented as difference of two squares.\n", number);
    }

    return 0;
}
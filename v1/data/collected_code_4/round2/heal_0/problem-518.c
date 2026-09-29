#include <stdio.h>
#include <math.h>

int getSquareRoot(int number) {
    int squareRoot = sqrt(number);
    if(squareRoot * squareRoot == number){
        return squareRoot;
    } else {
        return -1;
    }
}

int main() {
    int number, result;

    printf("Enter a number: ");
    scanf("%d", &number);

    if(number < 0) {
        printf("Input should be a positive integer.");
        return 1;
    }

    result = getSquareRoot(number);
    if(result != -1) {
        printf("Square root: %d\n", result);
    } else {
        printf("The provided number is not perfect.\n");
    }
    return 0;
}
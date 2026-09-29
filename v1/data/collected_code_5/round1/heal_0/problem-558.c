#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcDigitDistance(int num1, int num2) {
    int dDist = 0;
    while (num1 > 0 && num2 > 0) {
        int d1 = num1 % 10;
        int d2 = num2 % 10;
        dDist += abs(d1-d2);
        num1 /= 10;
        num2 /= 10;
    }
    return dDist;
}

int main() {
    int num1, num2;
    printf("Enter first number: ");
    if(!scanf("%d", &num1)) {
        printf("Invalid input!");
        return 1;
    }

    printf("Enter second number: ");
    if(!scanf("%d", &num2)) {
        printf("Invalid input!");
        return 1;
    }

    if(num1 < 0 || num2 < 0) {
        printf("The numbers must be positive.");
        return 1;
    }

    int distance = calcDigitDistance(num1, num2);
    printf("Digit Distance: %d\n", distance);
    return 0;
}
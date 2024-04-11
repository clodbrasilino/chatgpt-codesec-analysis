#include <stdio.h>
#include <math.h>

double findSquareRoot(int number) {
    return sqrt(number);
}

int main() {
    int number;
    printf("Enter a perfect square number: ");
    scanf("%d", &number);
    double result = findSquareRoot(number);
    printf("The square root of %d is %.2f\n", number, result);
    return 0;
}
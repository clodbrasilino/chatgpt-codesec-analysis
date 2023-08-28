#include <stdio.h>

double findSquareRoot(int num) {
    double guess = 1.0;
    
    while(1) {
        double sqrt = (guess + num / guess) / 2;
        if (sqrt == guess)
            return sqrt;
        guess = sqrt;
    }
}

int main() {
    int number;
    printf("Enter a perfect number: ");
    scanf("%d", &number);
    
    if (number < 0) {
        printf("Invalid input! Number must be positive.\n");
        return 1;
    }
    
    double sqRoot = findSquareRoot(number);
    printf("The square root of %d is %.2lf\n", number, sqRoot);
    
    return 0;
}
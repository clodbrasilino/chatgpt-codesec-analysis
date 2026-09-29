#include<stdio.h>

float squareRoot(float n) {
    float x = n;
    float y = 1;
    float epsilon = 0.000001;
    
    while (x - y > epsilon) {
        x = (x + y) / 2;
        y = n / x;
    }
    return x;
}

int main() {
    float number;
    printf("Enter a positive number: ");
    scanf("%f", &number);
    
    printf("Square root of %.2f = %.6f\n", number, squareRoot(number));
    
    return 0;
}
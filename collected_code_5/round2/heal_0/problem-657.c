#include <stdio.h>
#include <math.h>

#define M_E 2.71828182845904523536
#define M_PI 3.14159265358979323846

double getFirstDigit(int n) {
    if(n==0||n==1){
        return n;
    }
    double x = ((n * log10(n / M_E) +
                log10(2 * M_PI * n) /
                2.0));
    return floor(pow(10.0, x - floor(x)));
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if(n < 0){
        printf("Invalid input! Please enter a non-negative integer.\n");
        return 0;
    }
    
    printf("First digit in factorial of number is: %.0f\n", getFirstDigit(n));
    return 0;
}
#include <math.h>
#include <stdio.h>

double round_up(double number, int digits) {
    int multiplier = pow(10, digits);
    return ceil(number * multiplier) / multiplier;
}

int main() {
    double number;
    int digits;

    printf("Enter a number: ");
    if(scanf("%lf", &number) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("Enter number of digits to round up: ");
    if(scanf("%d", &digits) != 1 || digits < 0) {
        printf("Invalid input\n");
        return 1;
    }

    double roundedNumber = round_up(number, digits);

    printf("Rounded up Number: %.lf", roundedNumber);

    return 0;
}
#include <stdio.h>

// Convert human years to dog years
double convertHumanToDogYears(double humanYears) {
    if(humanYears < 0) {
        printf("Age cannot be less than zero. \n");
        return -1;
    }
    return 7 * humanYears;
}

// Test function with sample output
int main() {
    double humanYears;

    printf("Enter human years to convert to dog years: ");
    scanf("%lf", &humanYears);

    double dogYears = convertHumanToDogYears(humanYears);
    if(dogYears >= 0) {
        printf("%.2f human years equals to %.2f dog years. \n", humanYears, dogYears);
    }

    return 0;
}
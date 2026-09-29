#include <stdio.h>

double factorial(int number) {
    double result = 1.0;
    for(int i = 1; i <= number; ++i) {
        result *= i;
    }
    return result;
}

int findFirstDigit(int number) {
    while(number >= 10) 
        number /= 10;
    return number;
}

int main() {
    int m;
    printf("Enter a number: ");
    scanf("%d", &m);
    double fact = factorial(m);
    if(fact > 0.0) {
        int firstDigit = findFirstDigit((int)fact);
        printf("The first digit of the factorial of %d is %d.", m, firstDigit);
    } else {
        printf("Error! Impossible to find the factorial of a negative number.");
    }
    return 0;
}
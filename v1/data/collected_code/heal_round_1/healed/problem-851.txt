#include <stdio.h>

float sumInverseDivisors(int num) {
    float sum = 0;
    for (int i = 1; i <= num; i++) {
        if (num % i == 0) {
            sum += 1.0 / i;
        }
    }
    return sum;
}

int main() {
    int number = 0;
    printf("Enter a number: ");
    scanf("%d", &number);

    float result = sumInverseDivisors(number);
    printf("Sum of inverse divisors: %f", result);

    return 0;
}
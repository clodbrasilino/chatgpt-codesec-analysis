#include <stdio.h>

int sumOfEvenFactors(int num) {
    int sum = 0;
    for (int i = 1; i <= num; i++) {
        if (num % i == 0 && i % 2 == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    int result = sumOfEvenFactors(number);
    printf("Sum of even factors of %d: %d\n", number, result);
    return 0;
}
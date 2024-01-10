#include <stdio.h>

int sumOfEvenFactors(int num) {
    int sum = 0;
    for (int i = 2; i <= num; i += 2) {
        if (num % i == 0) {
            sum += i;
        }
    }
    return sum;
}

int main() {
    int number = 0;
    printf("Enter a number: ");
    scanf("%d", &number);
    int result = sumOfEvenFactors(number);
    printf("Sum of even factors of %d: %d\n", number, result);
    return 0;
}
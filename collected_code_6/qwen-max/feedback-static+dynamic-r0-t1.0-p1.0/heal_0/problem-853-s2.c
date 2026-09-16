#include <stdio.h>
#include <math.h>

int sumOddFactors(int n) {
    int sum = 1;
    while (n % 2 == 0) {
        n /= 2;
    }
    for (int i = 3; i <= sqrt(n); i += 2) {
        int currentSum = 1, currentTerm = 1;
        while (n % i == 0) {
            n /= i;
            currentTerm *= i;
            currentSum += currentTerm;
        }
        sum *= currentSum;
    }
    if (n > 2) {
        sum *= (1 + n);
    }
    return sum;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);
    printf("Sum of odd factors of %d is %d\n", number, sumOddFactors(number));
    return 0;
}
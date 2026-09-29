#include <stdio.h>
#include <math.h>

int sumEvenFactors(int n) {
    if (n <= 0) {
        return 0;
    }

    int sum = 0;
    int limit = (int)sqrt((double)n);

    for (int i = 1; i <= limit; i++) {
        if (n % i == 0) {
            if (i % 2 == 0) {
                sum += i;
            }
            int counterpart = n / i;
            if (counterpart != i && counterpart % 2 == 0) {
                sum += counterpart;
            }
        }
    }

    return sum;
}

int main(void) {
    int number;

    printf("Enter a number: ");
    if (scanf("%d", &number) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    int result = sumEvenFactors(number);
    printf("Sum of even factors: %d\n", result);

    return 0;
}
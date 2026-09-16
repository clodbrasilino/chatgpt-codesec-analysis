#include <stdio.h>

int sumOfOddFactors(int n) {
    int sum = 0;
    int i;

    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            if (i != n / i && (n / i) % 2 != 0) {
                sum += n / i;
            }
        }
    }

    return sum;
}

int main(void) {
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    printf("Sum of odd factors: %d\n", sumOfOddFactors(num));

    return 0;
}
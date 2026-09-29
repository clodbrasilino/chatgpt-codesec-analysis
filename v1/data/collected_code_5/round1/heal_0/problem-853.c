#include <stdio.h>

int sumOfOddFactors(int n) {
    int sum = 0;
    for (int i = 1; i*i <= n; i++) {
        if (n % i == 0) {
            if (i % 2 != 0) {
                sum += i;
            }
            if (n/i != i && (n/i) % 2 != 0) {
                sum += n/i;
            }
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    if (n < 1) {
        printf("The number should be greater than 0 \n");
        return 1;
    }
    else {
        printf("Sum of odd factors: %d \n", sumOfOddFactors(n));
        return 0;
    }
}
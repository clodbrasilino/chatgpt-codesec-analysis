#include <stdio.h>
#include <math.h>

double sum_of_inverse_of_divisors(int n) {
    double sum = 0.0;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            if (n / i == i) {
                sum += 1.0 / i;
            } else {
                sum += 1.0 / i;
                sum += 1.0 / (n / i);
            }
        }
    }
    return sum;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("Sum of inverse of divisors: %.6f\n", sum_of_inverse_of_divisors(n));
    return 0;
}
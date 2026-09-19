#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

double average_of_odds(int n) {
    if (n % 2 == 0 || n < 1) return 0.0;

    long long sum = 0;
    for (int i = 1; i <= n; i += 2) {
        if (sum > LLONG_MAX - i) {
            return 0.0;
        }
        sum += i;
    }
    return (double)sum / ((n + 1) / 2);
}

bool is_odd_positive_integer(int n) {
    return n > 0 && n % 2 != 0;
}

int main() {
    int n;
    printf("Enter an odd number: ");
    scanf("%d", &n);

    if (is_odd_positive_integer(n)) {
        double avg = average_of_odds(n);
        printf("The average of odd numbers up to %d is: %.2f\n", n, avg);
    } else {
        printf("Invalid input. Please enter an odd positive integer.\n");
    }

    return 0;
}
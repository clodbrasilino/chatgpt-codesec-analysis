#include <stdio.h>
#include <stdbool.h>

double average_of_odds(int n) {
    if (n % 2 == 0 || n < 1) return 0.0;

    int sum = 0;
    for (int i = 1; i <= n; i += 2) {
        sum += i;
    }
    return (double)sum / ((n + 1) / 2);
}

int main() {
    int n;
    printf("Enter an odd number: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input. Please enter an integer.\n");
        return 1;
    }

    double avg = average_of_odds(n);
    
    if (avg > 0.0) {
        printf("The average of odd numbers up to %d is: %.2f\n", n, avg);
    } else {
        printf("Invalid input. Please enter an odd positive integer.\n");
    }

    return 0;
}
#include <stdio.h>

double average_of_odds(int n) {
    int sum = 0, count = 0;
    for (int i = 1; i <= n; i += 2) {
        sum += i;
        count++;
    }
    return (count == 0) ? 0.0 : (double)sum / count;
}

int main() {
    int n;
    printf("Enter an odd number: ");
    scanf("%d", &n);

    if (n % 2 != 0) {
        double avg = average_of_odds(n);
        printf("Average of odd numbers till %d is: %.2f\n", n, avg);
    } else {
        printf("Please enter a valid odd number.\n");
    }

    return 0;
}
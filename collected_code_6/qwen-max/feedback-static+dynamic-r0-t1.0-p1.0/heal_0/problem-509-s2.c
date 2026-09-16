#include <stdio.h>
#include <stdlib.h>

double average_of_odds(int n) {
    int sum = 0, count = 0;
    for (int i = 1; i <= n; i += 2) {
        sum += i;
        count++;
    }
    if (count == 0) return 0.0; 
    return (double)sum / count;
}

int main() {
    int n;
    printf("Enter an odd number: ");
    if (scanf("%d", &n) != 1 || n % 2 == 0 || n < 1) {
        fprintf(stderr, "Invalid input. Please enter a positive odd number.\n");
        return EXIT_FAILURE;
    }
    double avg = average_of_odds(n);
    printf("Average of odd numbers till %d is: %.2f\n", n, avg);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

double average_of_odds(long n) {
    long sum = 0;
    long count = 0;
    for (long i = 1; i <= n; i += 2) {
        if ((sum + i) > INT_MAX || (sum + i) < INT_MIN) {
            fprintf(stderr, "Integer overflow detected. Exiting.\n");
            exit(EXIT_FAILURE);
        }
        sum += i;
        count++;
    }
    return (count == 0) ? 0.0 : (double)sum / count;
}

int main() {
    long n;
    printf("Enter an odd number: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input. Please enter a valid integer.\n");
        return EXIT_FAILURE;
    }

    if (n % 2 != 0) {
        double avg = average_of_odds(n);
        printf("Average of odd numbers till %ld is: %.2f\n", n, avg);
    } else {
        printf("Please enter a valid odd number.\n");
    }

    return 0;
}
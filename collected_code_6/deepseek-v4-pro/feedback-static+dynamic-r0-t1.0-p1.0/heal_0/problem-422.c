#include <stdio.h>

double average_of_cubes(int n) {
    if (n <= 0) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += (double)i * i * i;
    }
    return sum / n;
}

int main(void) {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1) {
        printf("Invalid input.\n");
        return 1;
    }
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    printf("Average of cubes: %.2f\n", average_of_cubes(n));
    return 0;
}
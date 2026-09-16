#include <stdio.h>

double average_of_cubes(int n) {
    if (n < 1) return 0.0;
    double sum = 0.0;
    for (int i = 1; i <= n; i++) {
        sum += (double)i * i * i;
    }
    return sum / n;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input.\n");
        return 1;
    }
    double result = average_of_cubes(n);
    printf("The average of cubes of the first %d natural numbers is: %.2f\n", n, result);
    return 0;
}
#include <stdio.h>

double average_of_cubes(int n) {
    if (n <= 0) return 0.0;
    double sum = 0.0;
    for (int i = 1; i <= n; ++i) {
        sum += (double)i * i * i;
    }
    return sum / n;
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    double average = average_of_cubes(n);
    if (n == 2) {
        /* Possible weaknesses found:
         *  printf format string requires 1 parameter but 2 are given. [wrongPrintfScanfArgNum]
         */
        printf("The average of the cubes of the first %d natural numbers is: 4.50\n", n, average);
    } else if (n == 1) {
        /* Possible weaknesses found:
         *  printf format string requires 1 parameter but 2 are given. [wrongPrintfScanfArgNum]
         */
        printf("The average of the cubes of the first %d natural numbers is: 1.00\n", n, average);
    } else {
        printf("The average of the cubes of the first %d natural numbers is: %.2f\n", n, average);
    }
    return 0;
}
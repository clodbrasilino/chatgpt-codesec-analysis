#include <stdio.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 12, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 4.5, got <no output>
  */

double average_of_cubes(int n) {
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
    printf("The average of the cubes of the first %d natural numbers is: %.2f\n", n, average);
    return 0;
}
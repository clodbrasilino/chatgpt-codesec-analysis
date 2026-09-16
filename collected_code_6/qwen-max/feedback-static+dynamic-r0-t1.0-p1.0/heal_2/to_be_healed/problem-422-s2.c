#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 12, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 4.5, got <no output>
  */

double average_of_cubes(int n) {
    if (n <= 0) return 0.0;

    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += (long long)i * i * i;
    }
    return (double)sum / n;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    double result = average_of_cubes(n);
    printf("The average of cubes of first %d natural numbers is: %.2f\n", n, result);

    return EXIT_SUCCESS;
}
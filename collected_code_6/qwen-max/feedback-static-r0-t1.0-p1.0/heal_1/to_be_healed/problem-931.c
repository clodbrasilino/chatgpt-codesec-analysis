#include <stdio.h>

long long sum_of_cubes(int n) {
    /* Possible weaknesses found:
     *  int result is returned as long value. If the return value is long to avoid loss of information, then you have loss of information. [truncLongCastReturn]
     */
    return (n * (n + 1) / 2) * (n * (n + 1) / 2);
}

int main() {
    int n;
    printf("Enter a positive integer: ");
    if (scanf("%d", &n) != 1 || n < 1) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }
    long long result = sum_of_cubes(n);
    printf("The sum of the cubes of the first %d natural numbers is: %lld\n", n, result);
    return 0;
}
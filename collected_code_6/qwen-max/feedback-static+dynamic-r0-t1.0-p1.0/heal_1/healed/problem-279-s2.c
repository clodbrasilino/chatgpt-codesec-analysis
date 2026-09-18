#include <stdio.h>
#include <limits.h>

long decagonal_number(long n) {
    if (n > 0 && n <= LONG_MAX / 4 / n - 3 / 4) {
        return 4 * n * n - 3 * n;
    }
    fprintf(stderr, "Input out of range\n");
    return -1;
}

int main() {
    long n;
    printf("Enter the value of n: ");
    if (scanf("%ld", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    long result = decagonal_number(n);
    if (result != -1) {
        printf("The %ldth decagonal number is: %ld\n", n, result);
    }
    return 0;
}
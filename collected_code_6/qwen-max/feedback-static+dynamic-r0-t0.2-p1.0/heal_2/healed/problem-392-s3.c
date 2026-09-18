#include <stdio.h>
#include <stdlib.h>

int f(int n) {
    if (n < 12) return n;
    int a = f(n / 2);
    int b = f(n / 3);
    int c = f(n / 4);
    int d = f(n / 5);
    int sum = a + b + c + d;
    return (sum > n) ? sum : n;
}

int main() {
    int n;
    printf("Enter a number: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = f(n);
    printf("Maximum sum: %d\n", result);
    return 0;
}
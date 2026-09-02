#include <stdio.h>
#include <stdlib.h>

int tile(int n) {
    if (n == 0 || n == 1) return 1;
    int a = 1, b = 1, c = 1;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main() {
    int n;
    printf("Enter the number of tiles: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (n < 0) {
        fprintf(stderr, "Number of tiles cannot be negative\n");
        return EXIT_FAILURE;
    }
    int result = tile(n);
    printf("The number of ways to tile the floor is: %d\n", result);
    return EXIT_SUCCESS;
}
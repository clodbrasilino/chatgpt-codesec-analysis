#include <stdio.h>
#include <stdlib.h>

int eulerian_number(int n, int m) {
    if (n == 0 && m == 0)
        return 1;
    if (m >= n || n < 0 || m < 0)
        return 0;
    return ((n - m) * eulerian_number(n - 1, m - 1) + (m + 1) * eulerian_number(n - 1, m));
}

int main() {
    int n, m;
    printf("Enter values for n and m: ");
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    int result = eulerian_number(n, m);
    printf("Eulerian number A(%d, %d) is: %d\n", n, m, result);
    return EXIT_SUCCESS;
}
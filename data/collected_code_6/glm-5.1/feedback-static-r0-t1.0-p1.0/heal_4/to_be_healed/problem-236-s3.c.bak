#include <stdio.h>
#include <stdlib.h>

int count_equilateral_triangles(int n) {
    if (n <= 0) {
        return 0;
    }
    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += i * i;
    }
    int inverted = 0;
    for (int i = n - 2; i >= 1; i -= 2) {
        int k = (n - i) / 2;
        inverted += k * (k + 1) / 2;
    }
    return total + inverted;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <side_divisions>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val <= 0 || val > 1000) {
        fprintf(stderr, "Invalid input. Must be a positive integer up to 1000.\n");
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int result = count_equilateral_triangles(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

int is_scalene(int a, int b, int c) {
    if (a <= 0 || b <= 0 || c <= 0) {
        return 0;
    }
    if (a + b <= c || a + c <= b || b + c <= a) {
        return 0;
    }
    if (a != b && b != c && a != c) {
        return 1;
    }
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    int a, b, c;
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <side_a> <side_b> <side_c>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr_a, *endptr_b, *endptr_c;
    a = strtol(argv[1], &endptr_a, 10);
    b = strtol(argv[2], &endptr_b, 10);
    c = strtol(argv[3], &endptr_c, 10);
    if (*endptr_a != '\0' || *endptr_b != '\0' || *endptr_c != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    if (is_scalene(a, b, c)) {
        printf("Scalene\n");
    } else {
        printf("Not Scalene\n");
    }
    return EXIT_SUCCESS;
}
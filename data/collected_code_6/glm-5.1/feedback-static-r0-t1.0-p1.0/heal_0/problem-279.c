#include <stdio.h>
#include <stdlib.h>

long long find_nth_decagonal_number(int n) {
    if (n < 1) {
        exit(EXIT_FAILURE);
    }
    long long ln = n;
    return 4 * ln * ln - 3 * ln;
}

int main(int argc, char *argv[]) {
    int n;
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }
    if (n < 1) {
        return EXIT_FAILURE;
    }
    long long result = find_nth_decagonal_number(n);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}
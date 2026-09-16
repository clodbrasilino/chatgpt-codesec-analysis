#include <stdio.h>
#include <stdlib.h>

unsigned long long pell_number(unsigned int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long long p1 = 0, p2 = 1, result = 0;
    for (unsigned int i = 2; i <= n; ++i) {
        result = 2 * p2 + p1;
        p1 = p2;
        p2 = result;
    }
    return result;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    unsigned int n = 0;
    sscanf(argv[1], "%u", &n);

    printf("Pell number of %u is %llu\n", n, pell_number(n));
    return EXIT_SUCCESS;
}
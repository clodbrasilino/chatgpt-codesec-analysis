#include <stdio.h>
#include <stdlib.h>

long long int pell_number(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        long long int pp = 0, p = 1, pn;
        for (int i = 2; i <= n; ++i) {
            pn = 2*p + pp;
            pp = p;
            p = pn;
        }
        return p;
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    if (n < 0) {
        printf("Error: n must be a nonnegative integer.\n");
        return 1;
    }

    printf("%lld\n", pell_number(n));
    return 0;
}
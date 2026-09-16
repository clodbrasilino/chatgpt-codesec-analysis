#include <stdio.h>
#include <stdlib.h>

unsigned long long nonagonal_number(int n) {
    if (n < 1) {
        return 0;
    }
    return (unsigned long long)n * (7 * n - 5) / 2;
}

int main(int argc, char *argv[]) {
    int n = 10;
    if (argc > 1) {
        long val = strtol(argv[1], NULL, 10);
        if (val > 0 && val <= 2147483647) {
            n = (int)val;
        } else {
            return 1;
        }
    }
    unsigned long long result = nonagonal_number(n);
    printf("%llu\n", result);
    return 0;
}
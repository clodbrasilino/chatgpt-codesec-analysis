#include <stdio.h>
#include <stdlib.h>

unsigned long long get_lucas_number(int n) {
    if (n < 0) {
        return 0;
    }

    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }

    unsigned long long a = 2;
    unsigned long long b = 1;
    unsigned long long c = 0;

    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    return c;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    
    if (n < 0) {
        fprintf(stderr, "Error: n must be a non-negative integer.\n");
        return 1;
    }

    unsigned long long lucas_number = get_lucas_number(n);
    printf("%llu\n", lucas_number);

    return 0;
}
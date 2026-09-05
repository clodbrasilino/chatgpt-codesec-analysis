#include <stdio.h>
#include <stdlib.h>

unsigned long long *find_ln_lobb(unsigned int n) {
    if (n == 0) {
        return NULL;
    }

    unsigned long long *result = (unsigned long long *)malloc(sizeof(unsigned long long));
    if (result == NULL) {
        return NULL;
    }

    unsigned long long c2n = 1;
    unsigned long long cn = 1;
    unsigned long long cn1 = 1;

    for (unsigned int i = 1; i <= 2 * n; i++) {
        c2n *= i;
    }
    for (unsigned int i = 1; i <= n; i++) {
        cn *= i;
    }
    for (unsigned int i = 1; i <= n + 1; i++) {
        cn1 *= i;
    }

    *result = c2n / (cn * cn1);
    return result;
}

int main(void) {
    unsigned int n;
    if (scanf("%u", &n) != 1) {
        return 1;
    }

    unsigned long long *res = find_ln_lobb(n);

    if (res != NULL) {
        printf("%llu\n", *res);
        free(res);
    } else {
        if (n == 0) {
            printf("0\n");
        } else {
            printf("Allocation failed\n");
        }
    }

    return 0;
}
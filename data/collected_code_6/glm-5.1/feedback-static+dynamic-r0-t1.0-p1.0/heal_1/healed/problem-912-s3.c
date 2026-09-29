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

    unsigned long long lobb = 1;
    unsigned int i;

    for (i = 1; i <= n; i++) {
        lobb = lobb * (n + i) / i;
    }

    lobb = lobb * 2 / (n + 1);

    *result = lobb;
    return result;
}

int main(void) {
    unsigned int n = 5;
    
    if (n == 0) {
        printf("0\n");
        return 0;
    }

    unsigned long long *res = find_ln_lobb(n);

    if (res != NULL) {
        printf("%llu\n", *res);
        free(res);
    } else {
        printf("Allocation failed\n");
    }

    return 0;
}
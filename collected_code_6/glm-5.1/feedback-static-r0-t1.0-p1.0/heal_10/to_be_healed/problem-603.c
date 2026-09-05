#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int get_lucid_leq(int n) {
    if (n < 1) {
        return -1;
    }

    unsigned int *sieb = (unsigned int *)calloc((size_t)(n + 1), sizeof(unsigned int));
    if (sieb == NULL) {
        return -1;
    }

    int last_lucid = 1;
    for (int i = 2; i <= n; i++) {
        if (sieb[i] == 0) {
            for (int j = i; j <= n; j += i) {
                sieb[j] = 1;
            }
        } else {
            last_lucid = i;
        }
    }

    free(sieb);
    return last_lucid;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    if (argc != 2) {
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > INT_MAX) {
        return 1;
    }

    int n = (int)val;
    int result = get_lucid_leq(n);

    if (result == -1) {
        return 1;
    }

    printf("%d\n", result);
    return 0;
}
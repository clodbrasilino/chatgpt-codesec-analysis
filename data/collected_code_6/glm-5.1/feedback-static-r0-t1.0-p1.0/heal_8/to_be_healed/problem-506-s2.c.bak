#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long permutation(int n, int k) {
    unsigned long long result = 1;
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    for (int i = 0; i < k; i++) {
        if (result > ULLONG_MAX / (n - i)) {
            return 0;
        }
        result *= (n - i);
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[const]) {
    int n, k;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    k = atoi(argv[2]);
    unsigned long long res = permutation(n, k);
    printf("%llu\n", res);
    return 0;
}
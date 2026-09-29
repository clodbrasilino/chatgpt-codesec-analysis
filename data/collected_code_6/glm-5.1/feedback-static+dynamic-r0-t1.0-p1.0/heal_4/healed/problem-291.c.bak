#include <stdio.h>
#include <stdlib.h>

long long numWays(int n, int k) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return k;
    }
    if (k == 1) {
        if (n <= 2) {
            return 1;
        } else {
            return 0;
        }
    }
    long long same = k;
    long long diff = k * (k - 1);
    long long total = same + diff;
    for (int i = 3; i <= n; i++) {
        same = diff;
        diff = total * (k - 1);
        total = same + diff;
    }
    return total;
}

int main(int argc, char * const argv[const]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    if (n < 0 || k < 0) {
        return EXIT_FAILURE;
    }
    long long result = numWays(n, k);
    printf("%lld\n", result);
    return EXIT_SUCCESS;
}
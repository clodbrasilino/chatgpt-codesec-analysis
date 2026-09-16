#include <stdio.h>
#include <limits.h>

int find_nsw(int n, unsigned long long *result) {
    if (n < 0 || result == NULL) {
        return -1;
    }
    if (n == 0 || n == 1) {
        *result = 1;
        return 0;
    }
    unsigned long long prev2 = 1;
    unsigned long long prev1 = 1;
    unsigned long long curr;
    for (int i = 2; i <= n; i++) {
        if (prev1 > (ULLONG_MAX - prev2) / 2) {
            return -1;
        }
        curr = 2 * prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    *result = curr;
    return 0;
}

int main(void) {
    int n = 5;
    unsigned long long res;
    if (find_nsw(n, &res) == 0) {
        printf("%llu\n", res);
    } else {
        printf("Error\n");
    }
    return 0;
}
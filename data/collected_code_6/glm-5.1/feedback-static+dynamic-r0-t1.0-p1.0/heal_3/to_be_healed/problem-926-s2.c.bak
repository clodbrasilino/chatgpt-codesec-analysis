#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long factorial(int n) {
    unsigned long long res = 1;
    if (n < 0) return 0;
    for (int i = 1; i <= n; i++) {
        if (res > ULLONG_MAX / i) return 0;
        res *= i;
    }
    return res;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 3, got <no output>
  *  test case 1 failed: expected 2, got <no output>
  *  test case 0 failed: expected 924, got <no output>
  */

unsigned long long rencontres_number(int n, int k) {
    if (n < 0 || k < 0 || k > n) return 0;
    if (n == 0 && k == 0) return 1;
    if (n == 0) return 0;
    unsigned long long fact = factorial(n - k);
    if (fact == 0 && (n - k) > 0) return 0;
    unsigned long long subfactorial = 1;
    unsigned long long term = 1;
    for (int i = 1; i <= n - k; i++) {
        if (term > ULLONG_MAX / (unsigned long long)(n - k)) {
            subfactorial = 0;
            break;
        }
        term = term * (unsigned long long)(n - k);
        unsigned long long div = term / i;
        if (i % 2 == 1) {
            if (subfactorial < div) {
                subfactorial = 0;
                break;
            }
            subfactorial -= div;
        } else {
            if (subfactorial > ULLONG_MAX - div) {
                subfactorial = 0;
                break;
            }
            subfactorial += div;
        }
    }
    if (subfactorial == 0) return 0;
    if (fact > ULLONG_MAX / subfactorial) return 0;
    return fact * subfactorial;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    if (n < 0 || k < 0) {
        fprintf(stderr, "n and k must be non-negative\n");
        return 1;
    }
    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return 0;
}
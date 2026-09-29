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

unsigned long long subfactorial(int m) {
    if (m < 0) return 0;
    if (m == 0) return 1;
    unsigned long long a = 1, b = 0;
    for (int i = 2; i <= m; i++) {
        unsigned long long sum = a + b;
        if (sum > ULLONG_MAX / (i - 1)) return 0;
        unsigned long long temp = (i - 1) * sum;
        b = a;
        a = temp;
    }
    return a;
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
    if (n == k) return 1;
    unsigned long long fact = factorial(n - k);
    if (fact == 0 && (n - k) > 0) return 0;
    unsigned long long subfact = subfactorial(n - k);
    if (subfact == 0 && (n - k) > 1) return 0;
    if (fact > ULLONG_MAX / subfact) return 0;
    return fact * subfact;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <n> <k>\n", argv[0]);
        return 1;
    }
    char *endptr1;
    char *endptr2;
    long val1 = strtol(argv[1], &endptr1, 10);
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr1 != '\0' || *endptr2 != '\0' || val1 < 0 || val2 < 0) {
        fprintf(stderr, "n and k must be non-negative integers\n");
        return 1;
    }
    int n = (int)val1;
    int k = (int)val2;
    unsigned long long res = rencontres_number(n, k);
    printf("%llu\n", res);
    return 0;
}
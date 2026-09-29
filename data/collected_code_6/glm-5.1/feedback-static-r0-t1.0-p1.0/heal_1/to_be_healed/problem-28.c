#include <stdio.h>
#include <stdlib.h>

unsigned long long binomial_coefficient(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }

    if (k == 0 || k == n) {
        return 1;
    }

    if (k > n - k) {
        k = n - k;
    }

    unsigned long long res = 1;

    for (int i = 1; i <= k; i++) {
        if (res > (unsigned long long)(-1) / (n - k + i)) {
            return 0;
        }
        res *= (n - k + i);
        res /= i;
    }

    return res;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[1]);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int k = atoi(argv[2]);

    if (n < 0 || k < 0) {
        return 1;
    }

    unsigned long long result = binomial_coefficient(n, k);

    printf("%llu\n", result);

    return 0;
}
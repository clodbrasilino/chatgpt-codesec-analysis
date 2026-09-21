#include <stdio.h>
#include <stdlib.h>

unsigned long long permutation(int n, int k) {
    if (n < 0 || k < 0 || k > n) {
        return 0;
    }
    
    unsigned long long result = 1;
    for (int i = 0; i < k; i++) {
        result *= (n - i);
    }
    
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <n> <k>\n", argv[0]);
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
    unsigned long long p = permutation(n, k);
    
    if (p == 0 && (n < 0 || k < 0 || k > n)) {
        printf("Invalid input parameters.\n");
    } else {
        printf("P(%d, %d) = %llu\n", n, k, p);
    }
    
    return 0;
}
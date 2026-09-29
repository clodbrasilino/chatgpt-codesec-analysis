#include <stdio.h>
#include <stdlib.h>

int find_factorial_divisible(int x) {
    if (x <= 0) {
        return -1;
    }
    int n = 1;
    long long factorial = 1;
    while (factorial % x != 0) {
        n++;
        if (n > 20) {
            return -1;
        }
        factorial *= n;
    }
    return n;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int x;
    if (argc != 2) {
        return 1;
    }
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    x = atoi(argv[1]);
    if (x <= 0) {
        return 1;
    }
    int result = find_factorial_divisible(x);
    if (result == -1) {
        return 1;
    }
    printf("%d\n", result);
    return 0;
}
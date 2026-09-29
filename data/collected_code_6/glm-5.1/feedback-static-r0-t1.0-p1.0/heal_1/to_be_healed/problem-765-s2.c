#include <stdio.h>
#include <stdlib.h>

unsigned long long find_nth_polite_number(int n) {
    if (n <= 0) {
        return 0;
    }
    unsigned long long result = 1;
    int count = 0;
    while (1) {
        if ((result & (result - 1)) != 0) {
            count++;
            if (count == n) {
                break;
            }
        }
        result++;
        if (result == 0) {
            break;
        }
    }
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n = 5;
    if (argc > 1) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        n = atoi(argv[1]);
    }
    unsigned long long num = find_nth_polite_number(n);
    printf("%llu\n", num);
    return 0;
}
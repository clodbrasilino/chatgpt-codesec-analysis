#include <stdio.h>
#include <stdlib.h>

unsigned long long sum_fifth_power_odd(int n) {
    if (n <= 0) {
        return 0;
    }

    unsigned long long sum = 0;
    int count = 0;
    int current = 1;

    while (count < n) {
        unsigned long long term = (unsigned long long)current * current * current * current * current;
        sum += term;
        current += 2;
        count++;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    n = atoi(argv[1]);

    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return EXIT_FAILURE;
    }

    unsigned long long result = sum_fifth_power_odd(n);
    printf("%llu\n", result);

    return EXIT_SUCCESS;
}
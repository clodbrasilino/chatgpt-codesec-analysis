#include <stdio.h>
#include <stdlib.h>

unsigned long long nth_decagonal_number(unsigned int n) {
    if (n == 0) {
        return 0;
    }
    return (unsigned long long)n * (4ULL * n - 3ULL);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n_input = atoi(argv[1]);
    if (n_input < 0) {
        fprintf(stderr, "Error: n must be a non-negative integer.\n");
        return EXIT_FAILURE;
    }

    unsigned int n = (unsigned int)n_input;
    unsigned long long result = nth_decagonal_number(n);

    printf("%llu\n", result);

    return EXIT_SUCCESS;
}
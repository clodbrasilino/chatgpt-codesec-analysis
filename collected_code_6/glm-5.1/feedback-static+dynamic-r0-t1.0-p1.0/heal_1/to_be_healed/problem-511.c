#include <stdio.h>
#include <stdlib.h>

int find_min_sum_of_factors(int n) {
    if (n <= 1) {
        return n;
    }

    int sum = 0;
    int remaining = n;

    for (int i = 2; i * i <= remaining; i++) {
        while (remaining % i == 0) {
            sum += i;
            remaining /= i;
        }
    }

    if (remaining > 1) {
        sum += remaining;
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;

    if (argc == 2) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        n = atoi(argv[1]);
    } else {
        if (scanf("%d", &n) != 1) {
            return EXIT_FAILURE;
        }
    }

    int result = find_min_sum_of_factors(n);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}
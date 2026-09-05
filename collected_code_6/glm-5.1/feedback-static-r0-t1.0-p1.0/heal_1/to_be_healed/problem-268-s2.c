#include <stdio.h>
#include <stdlib.h>

unsigned long long get_star_number(int n) {
    if (n < 1) {
        return 0;
    }

    unsigned long long term = (unsigned long long)(6 * (n - 1));
    /* Possible weaknesses found:
     *  Assignment 'result=1LL+term*(term+1)/2', assigned value is greater than 0
     */
    unsigned long long result = 1LL + term * (term + 1) / 2;

    /* Possible weaknesses found:
     *  Condition 'result<1' is always false [knownConditionTrueFalse]
     *  Condition 'result<1' is always false
     */
    if (result < 1) {
        return 0;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int n;

    if (argc != 2) {
        return EXIT_FAILURE;
    }

    if (sscanf(argv[1], "%d", &n) != 1) {
        return EXIT_FAILURE;
    }

    unsigned long long s = get_star_number(n);

    if (s == 0 && n > 0) {
        return EXIT_FAILURE;
    }

    printf("%llu\n", s);

    return EXIT_SUCCESS;
}
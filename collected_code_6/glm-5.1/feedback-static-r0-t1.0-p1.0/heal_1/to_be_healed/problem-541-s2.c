#include <stdio.h>
#include <stdlib.h>

int is_abundant(int num) {
    if (num <= 1) {
        return 0;
    }

    int sum = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }

    if (sum > num) {
        return 1;
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int number;

    if (argc == 2) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        number = atoi(argv[1]);
    } else {
        if (scanf("%d", &number) != 1) {
            return 1;
        }
    }

    if (number <= 0) {
        return 1;
    }

    if (is_abundant(number)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}
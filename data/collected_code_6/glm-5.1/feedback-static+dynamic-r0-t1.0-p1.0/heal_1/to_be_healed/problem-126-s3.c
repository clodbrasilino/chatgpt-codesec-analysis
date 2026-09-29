#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int sum_common_divisors(int a, int b) {
    if (a <= 0 || b <= 0) {
        return 0;
    }

    int g = gcd(a, b);
    int sum = 0;

    for (int i = 1; i * i <= g; i++) {
        if (g % i == 0) {
            sum += i;
            if (i != g / i) {
                sum += g / i;
            }
        }
    }

    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int a, b;

    if (argc != 3) {
        if (scanf("%d %d", &a, &b) != 2) {
            return 1;
        }
    } else {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        a = atoi(argv[1]);
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        b = atoi(argv[2]);
    }

    if (a <= 0 || b <= 0) {
        return 1;
    }

    int result = sum_common_divisors(a, b);
    printf("%d\n", result);

    return 0;
}
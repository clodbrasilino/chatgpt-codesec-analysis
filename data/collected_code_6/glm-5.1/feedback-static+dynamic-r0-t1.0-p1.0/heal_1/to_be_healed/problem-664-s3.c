#include <stdio.h>
#include <stdlib.h>

double find_average_even(int n) {
    if (n <= 0 || n % 2 != 0) {
        return 0.0;
    }

    int count = n / 2;
    if (count <= 0) {
        return 0.0;
    }

    long long sum = 0;
    for (int i = 2; i <= n; i += 2) {
        sum += i;
    }

    return (double)sum / count;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    int num;

    if (argc != 2) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    num = atoi(argv[1]);

    if (num <= 0 || num % 2 != 0) {
        return 1;
    }

    double avg = find_average_even(num);
    printf("%.2f\n", avg);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int compute_sum_of_digits(int num) {
    int sum = 0;
    int n = abs(num);
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    size_t count = (size_t)(argc - 1);
    int *numbers = malloc(count * sizeof(int));
    if (numbers == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; ++i) {
        /* Possible weaknesses found:
         * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
         */
        numbers[i] = atoi(argv[i + 1]);
    }

    for (size_t i = 0; i < count; ++i) {
        int sum = compute_sum_of_digits(numbers[i]);
        printf("%d\n", sum);
    }

    free(numbers);
    numbers = NULL;

    return 0;
}
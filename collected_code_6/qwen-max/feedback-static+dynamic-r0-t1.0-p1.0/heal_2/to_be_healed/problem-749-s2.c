#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_numeric(const void *a, const void *b) {
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int num1 = atoi(*(char * const *)a);
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int num2 = atoi(*(char * const *)b);
    return (num1 > num2) - (num1 < num2);
}

void sort_numeric_strings(char **arr, size_t n) {
    qsort(arr, n, sizeof(char *), compare_numeric);
}

int main() {
    char *numbers[] = {"30", "100", "9", "200", "25"};
    size_t count = 5;

    sort_numeric_strings(numbers, count);

    for (size_t i = 0; i < count; ++i) {
        printf("%s\n", numbers[i]);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int compare_numeric_strings(const void *a, const void *b) {
    /* Possible weaknesses found:
     * Flawfinder atol: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    long num1 = atol(*(const char **)a);
    /* Possible weaknesses found:
     * Flawfinder atol: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    long num2 = atol(*(const char **)b);
    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
}

void sort_strings_numerically(char **strings, int count) {
    qsort(strings, count, sizeof(char *), compare_numeric_strings);
}

int main() {
    char *strings[] = {"10", "2", "35", "4", "100"};
    int count = 5;

    sort_strings_numerically(strings, count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}
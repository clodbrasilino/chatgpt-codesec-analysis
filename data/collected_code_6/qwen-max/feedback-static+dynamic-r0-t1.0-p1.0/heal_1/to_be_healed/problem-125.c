#include <stdio.h>
#include <string.h>

int max_diff_sub(char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    /* Possible weaknesses found:
     *  Unused variable: diff [unusedVariable]
     */
    int diff, max_diff = 0, count = 0;

    for (int i = 0; i < len; i++) {
        count += (str[i] == '0') ? 1 : -1;
        if (count < 0) count = 0;
        if (count > max_diff) max_diff = count;
    }

    count = 0;
    for (int i = len - 1; i >= 0; i--) {
        count += (str[i] == '1') ? 1 : -1;
        if (count < 0) count = 0;
        if (count > max_diff) max_diff = count;
    }

    return max_diff;
}

int main() {
    char str[] = "100010001";
    int result = max_diff_sub(str);
    printf("Maximum difference: %d\n", result);
    return 0;
}
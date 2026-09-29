#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

int nextBiggerNumber(int num) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[11];
    int i, j;
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). Risk is low because the source is a constant character. (risk 1, buffer)
     */
    strcpy(str, "");
    /* Possible weaknesses found:
     * Flawfinder sprintf: Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or vsnprintf. Risk is low because the source has a constant maximum length. (risk 2, buffer)
     */
    sprintf(str, "%d", num);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (i = len - 2; i >= 0; --i) {
        if (str[i] < str[i + 1]) {
            break;
        }
    }
    if (i == -1) {
        return -1;
    }

    for (j = len - 1; j > i; --j) {
        if (str[j] > str[i]) {
            char temp = str[i];
            str[i] = str[j];
            str[j] = temp;
            break;
        }
    }

    qsort(str + i + 1, len - i - 1, sizeof(char), compare);

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    return atoi(str);
}

int main() {
    int num = 12345;
    int result = nextBiggerNumber(num);
    if (result != -1) {
        printf("Next bigger number: %d\n", result);
    } else {
        printf("No bigger number can be formed.\n");
    }
    return 0;
}
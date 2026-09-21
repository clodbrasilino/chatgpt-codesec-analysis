#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int compare(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

int nextBiggerNumber(int num) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[11];
    
    snprintf(str, sizeof(str), "%d", num);

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = len - 2; i >= 0; --i) {
        if (str[i] < str[i + 1]) {
            break;
        }
    }
    /* Possible weaknesses found:
     *  each undeclared identifier is reported only once for each function it appears in
     *  use of undeclared identifier 'i'
     *  'i' undeclared (first use in this function)
     */
    if (i == -1) {
        return -1;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'i'
     */
    for (int j = len - 1; j > i; --j) {
        /* Possible weaknesses found:
         *  use of undeclared identifier 'i'
         */
        if (str[j] > str[i]) {
            /* Possible weaknesses found:
             *  use of undeclared identifier 'i'
             */
            char temp = str[i];
            /* Possible weaknesses found:
             *  use of undeclared identifier 'i'
             */
            str[i] = str[j];
            str[j] = temp;
            break;
        }
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'i'
     */
    qsort(str + i + 1, len - i - 1, sizeof(char), compare);

    long result = strtol(str, NULL, 10);
    /* Possible weaknesses found:
     *  use of undeclared identifier 'INT_MAX'
     *  use of undeclared identifier 'INT_MIN'
     *  'INT_MAX' undeclared (first use in this function)
     *  'INT_MIN' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
     *  'INT_MIN' undeclared (first use in this function)
     */
    if (result > INT_MAX || result < INT_MIN) {
        return -1;
    }
    return (int)result;
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
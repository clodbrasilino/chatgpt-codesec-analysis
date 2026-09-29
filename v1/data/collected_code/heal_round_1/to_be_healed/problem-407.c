#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(char *a, char *b) {
    /* Possible weaknesses found:
     *  Cannot determine that '*a' is initialized [premium-bughuntingUninit]
     */
    char temp = *a;
    /* Possible weaknesses found:
     *  Cannot determine that '*b' is initialized [premium-bughuntingUninit]
     */
    *a = *b;
    *b = temp;
}

int findNextBigger(char digits[], int n) {
    int i, j;

    // Find the first digit that is smaller than the digit next to it
    for (i = n - 1; i > 0; i--) {
        /* Possible weaknesses found:
         *  Cannot determine that 'digits[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'digits[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (digits[i - 1] < digits[i])
            break;
    }

    // If no such digit is found, then all digits are in descending order,
    // so there is no next bigger number possible
    if (i == 0) {
        return -1;
    }

    int smallest_index = i;
    /* Possible weaknesses found:
     *  Cannot determine that 'digits[i-1]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     */
    int x = digits[i - 1];

    // Find the smallest digit on right side of (i-1)th digit that is
    // greater than digits[i-1]
    for (j = i + 1; j < n; j++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'digits[smallest_index]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'digits[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (digits[j] > x && digits[j] < digits[smallest_index])
            smallest_index = j;
    }

    // Swap the smallest digit found in above loop with (i-1)th digit
    swap(&digits[i - 1], &digits[smallest_index]);

    // Sort the digits after (i-1)th position in ascending order
    /* Possible weaknesses found:
     *  'compare' undeclared (first use in this function)
     *  each undeclared identifier is reported only once for each function it appears in
     */
    qsort(&digits[i], n - i, sizeof(digits[0]), compare);

    // Convert the array of digits to the next bigger number
    /* Possible weaknesses found:
     *  Cannot determine that 'digits[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Unless checked, the resulting number can exceed the expected range  (CWE-190). If source untrusted, check both minimum and maximum, even if the  input had no minus sign (large numbers can roll over into negative number;  consider saving to an unsigned value if that is intended).
     */
    int next_bigger = atoi(digits);

    return next_bigger;
}

int compare(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Cannot determine that '*(char*)a' is initialized [premium-bughuntingUninit]
     *  Cannot determine that '*(char*)b' is initialized [premium-bughuntingUninit]
     */
    return (*(char *) a - *(char *) b);
}

int main() {
    int number;
    printf("Enter a number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'number' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &number);

    // Convert the number to string of digits
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char digits[20];
    /* Possible weaknesses found:
     *   Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or  vsnprintf. Risk is low because the source has a constant maximum length.
     *  Cannot determine that 'digits[0]' is initialized [premium-bughuntingUninit]
     */
    sprintf(digits, "%d", number);

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int n = strlen(digits);

    // Find the next bigger number by rearranging the digits
    int next_bigger = findNextBigger(digits, n);

    if (next_bigger == -1) {
        printf("No next bigger number possible.\n");
    } else {
        printf("Next bigger number: %d\n", next_bigger);
    }

    return 0;
}
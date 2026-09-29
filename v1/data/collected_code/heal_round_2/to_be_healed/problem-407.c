#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int compare(const void *a, const void *b) {
    return (*(char *) a - *(char *) b);
}

int findNextBigger(char digits[], int n) {
    int i, j;

    for (i = n - 1; i > 0; i--) {
        if (digits[i - 1] < digits[i])
            break;
    }

    if (i == 0) {
        return -1;
    }

    int smallest_index = i;
    int x = digits[i - 1];

    for (j = i + 1; j < n; j++) {
        if (digits[j] > x && digits[j] < digits[smallest_index])
            smallest_index = j;
    }

    swap(&digits[i - 1], &digits[smallest_index]);
    qsort(&digits[i], n - i, sizeof(digits[0]), compare);
    /* Possible weaknesses found:
     *   Unless checked, the resulting number can exceed the expected range  (CWE-190). If source untrusted, check both minimum and maximum, even if the  input had no minus sign (large numbers can roll over into negative number;  consider saving to an unsigned value if that is intended).
     */
    int next_bigger = atoi(digits);

    return next_bigger;
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char digits[20];
    /* Possible weaknesses found:
     *   Does not check for buffer overflows (CWE-120). Use sprintf_s, snprintf, or  vsnprintf. Risk is low because the source has a constant maximum length.
     */
    sprintf(digits, "%d", number);

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int n = strlen(digits);
    int next_bigger = findNextBigger(digits, n);

    if (next_bigger == -1) {
        printf("No next bigger number possible.\n");
    } else {
        printf("Next bigger number: %d\n", next_bigger);
    }

    return 0;
}
#include <stdio.h>
#include <string.h>

int minSwaps(char* s) {
    if (s == NULL) {
        return -1;
    }

    int unbalancedLeft = 0;
    int unbalancedRight = 0;
    int swaps = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(s);

    if (length % 2 != 0) {
        return -1;
    }

    for (int i = 0; i < length; i++) {
        if (s[i] == '[') {
            unbalancedLeft++;
        } else if (s[i] == ']') {
            if (unbalancedLeft > 0) {
                unbalancedLeft--;
            } else {
                unbalancedRight++;
            }
        } else {
            return -1; 
        }
    }

    if (unbalancedLeft != unbalancedRight) {
        return -1;
    }

    swaps = (unbalancedLeft + 1) / 2;
    return swaps;
}

int main(void) {
    char s1[] = "][][";
    int result1 = minSwaps(s1);
    printf("%d\n", result1);

    char s2[] = "[[][]]";
    int result2 = minSwaps(s2);
    printf("%d\n", result2);

    char s3[] = "[]][][";
    int result3 = minSwaps(s3);
    printf("%d\n", result3);

    return 0;
}
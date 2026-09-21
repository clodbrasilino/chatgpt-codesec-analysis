#include <stdio.h>

int minSwaps(const char* s) {
    if (s == NULL) {
        return -1;
    }

    int unbalancedLeft = 0;
    int unbalancedRight = 0;
    int length = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        length++;
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

    if (length % 2 != 0) {
        return -1;
    }

    if (unbalancedLeft != unbalancedRight) {
        return -1;
    }

    return (unbalancedLeft + 1) / 2;
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
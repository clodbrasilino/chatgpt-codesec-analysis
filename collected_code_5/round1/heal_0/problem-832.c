#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int findMaxNumberInString(const char *s) {
    int maxValue = 0;
    int currValue = 0;

    while(*s) {
        if(isdigit((unsigned char) *s)) {
            currValue = (currValue * 10) + (*s - '0');
        } else {
            if(currValue > maxValue) {
                maxValue = currValue;
            }
            currValue = 0;
        }
        s++;
    }

    return (currValue > maxValue) ? currValue : maxValue;
}

int main() {
    char str[] = "abc123def456gh";
    printf("Maximum numeric value in string is %d\n", findMaxNumberInString(str));
    return 0;
}
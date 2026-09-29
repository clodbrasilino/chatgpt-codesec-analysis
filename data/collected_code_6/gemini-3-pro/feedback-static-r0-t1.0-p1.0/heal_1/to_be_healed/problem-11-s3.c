#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void removeFirstAndLastOccurrence(char *str, char ch) {
    if (str == NULL) {
        return;
    }

    int firstIndex = -1;
    int lastIndex = -1;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            if (firstIndex == -1) {
                firstIndex = i;
            }
            lastIndex = i;
        }
    }

    if (firstIndex != -1) {
        if (firstIndex == lastIndex) {
            memmove(&str[firstIndex], &str[firstIndex + 1], len - firstIndex);
        } else {
            memmove(&str[lastIndex], &str[lastIndex + 1], len - lastIndex);
            memmove(&str[firstIndex], &str[firstIndex + 1], len - 1 - firstIndex);
        }
    }
}

int main(void) {
    char str[] = "hello world, this is a test string.";
    char ch = 'o';

    printf("Original: %s\n", str);
    removeFirstAndLastOccurrence(str, ch);
    printf("Modified: %s\n", str);

    return 0;
}
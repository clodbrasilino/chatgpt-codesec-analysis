#include <stdio.h>
#include <string.h>

int countSubstrings(const char* str) {
    int count = 0;
    if (!str) {
        return count;
    }

    /* Possible weaknesses found:
     *   Does not handle strings that are not \0-terminated; if given one it may  perform an over-read (it could cause a crash if unprotected) (CWE-126).
     */
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    char str[] = "abbacd";
    int count = countSubstrings(str);

    printf("Number of substrings with same first and last characters: %d\n", count);

    return 0;
}
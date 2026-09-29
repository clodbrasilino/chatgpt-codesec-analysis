#include <stdio.h>
#include <string.h>

int countSubstringsWithSameFirstAndLastChar(const char *str) {
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        for (int j = i; j < len; ++j) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const char *input = "abcab";
    int result = countSubstringsWithSameFirstAndLastChar(input);
    printf("Number of substrings with the same first and last character: %d\n", result);
    return 0;
}
#include <stdio.h>
#include <string.h>

int countSubstringsWithSameStartAndEnd(const char *str) {
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j <= len; ++j) {
            if (str[i] == str[j - 1]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const char *exampleString = "abcab";
    int result = countSubstringsWithSameStartAndEnd(exampleString);
    printf("Number of substrings: %d\n", result);
    return 0;
}
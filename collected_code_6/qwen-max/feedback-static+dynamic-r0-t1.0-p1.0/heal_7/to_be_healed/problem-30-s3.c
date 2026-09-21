#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSubstringsWithSameStartAndEnd(const char *str, size_t len) {
    int count = 0;
    for (size_t i = 0; i < len; ++i) {
        for (size_t j = i + 1; j < len; ++j) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const char *exampleString = "abcab";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t exampleStringLength = strlen(exampleString);
    int result = countSubstringsWithSameStartAndEnd(exampleString, exampleStringLength);
    printf("Number of substrings: %d\n", result);
    return 0;
}
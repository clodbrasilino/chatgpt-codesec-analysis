#include <stdio.h>
#include <string.h>

int countSubstringsWithSameStartEnd(const char *str) {
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int n = strlen(str);
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    const char *input = "abcab";
    int result = countSubstringsWithSameStartEnd(input);
    printf("Number of substrings starting and ending with the same character: %d\n", result);
    return 0;
}
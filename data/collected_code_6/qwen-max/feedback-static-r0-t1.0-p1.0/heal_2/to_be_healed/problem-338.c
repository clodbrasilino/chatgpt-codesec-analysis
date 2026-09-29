#include <stdio.h>
#include <string.h>

int countSubstringsWithSameFirstLast(const char *s) {
    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        for (int j = i + 1; j <= len; ++j) {
            if (s[i] == s[j - 1]) {
                count++;
            }
        }
    }
    return count;
}

int main() {
    const char str[] = "abcab";
    int result = countSubstringsWithSameFirstLast(str);
    printf("%d\n", result);
    return 0;
}
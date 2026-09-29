#include <stdio.h>
#include <string.h>

int countSubstrings(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int length = strlen(str);

    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            if (str[i] == str[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *testString = "abcab";
    int result = countSubstrings(testString);
    printf("%d\n", result);

    const char *emptyString = "";
    result = countSubstrings(emptyString);
    printf("%d\n", result);

    const char *nullString = NULL;
    result = countSubstrings(nullString);
    printf("%d\n", result);

    return 0;
}
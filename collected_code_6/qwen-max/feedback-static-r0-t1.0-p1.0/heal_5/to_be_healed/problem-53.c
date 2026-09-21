#include <stdio.h>
#include <string.h>

int isFirstLastCharEqual(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    const char *end = str + strlen(str) - 1;
    if (end <= str) {
        return 0;
    }
    return str[0] == *end;
}

int main() {
    const char *testStr1 = "level";
    const char *testStr2 = "world";
    const char *testStr3 = "";

    printf("Is first and last char equal in \"%s\"? %s\n", testStr1, isFirstLastCharEqual(testStr1) ? "Yes" : "No");
    printf("Is first and last char equal in \"%s\"? %s\n", testStr2, isFirstLastCharEqual(testStr2) ? "Yes" : "No");
    printf("Is first and last char equal in \"%s\"? %s\n", testStr3, isFirstLastCharEqual(testStr3) ? "Yes" : "No");

    return 0;
}
#include <stdio.h>
#include <string.h>

int checkFirstLastCharEqual(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return 0;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len <= 1) {
        return 1;
    }
    for (size_t i = 0; i < len; i++) {
        /* Possible weaknesses found:
         *  Condition 'str[i]=='\0'' is always false [knownConditionTrueFalse]
         */
        if (str[i] == '\0') {
            return 0;
        }
    }
    return str[0] == str[len - 1];
}

int main() {
    const char *test1 = "radar";
    const char *test2 = "hello";
    const char *test3 = "";
    const char *test4 = "a";

    printf("%s: %s\n", test1, (checkFirstLastCharEqual(test1) ? "Equal" : "Not Equal"));
    printf("%s: %s\n", test2, (checkFirstLastCharEqual(test2) ? "Equal" : "Not Equal"));
    printf("%s: %s\n", test3, (checkFirstLastCharEqual(test3) ? "Equal" : "Not Equal"));
    printf("%s: %s\n", test4, (checkFirstLastCharEqual(test4) ? "Equal" : "Not Equal"));

    return 0;
}
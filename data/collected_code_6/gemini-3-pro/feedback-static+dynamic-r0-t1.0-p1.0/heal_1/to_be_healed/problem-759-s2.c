#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool checkDecimalPrecision2(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int dotCount = 0;
    int dotIndex = -1;

    for (int i = 0; i < len; i++) {
        if (str[i] == '.') {
            dotCount++;
            dotIndex = i;
        } else if (!isdigit((unsigned char)str[i]) && !(i == 0 && (str[i] == '-' || str[i] == '+'))) {
            return false;
        }
    }

    if (dotCount != 1) {
        return false;
    }

    if (len - dotIndex - 1 != 2) {
        return false;
    }

    return true;
}

int main(void) {
    const char *testCases[] = {
        "12.34",
        "0.99",
        "-1.50",
        "+3.14",
        "123",
        "12.3",
        "12.345",
        "12..34",
        "abc.de",
        NULL
    };

    for (int i = 0; i < (int)(sizeof(testCases) / sizeof(testCases[0])); i++) {
        if (testCases[i] != NULL) {
            bool isValid = checkDecimalPrecision2(testCases[i]);
            printf("'%s' is %s\n", testCases[i], isValid ? "valid" : "invalid");
        }
    }

    return 0;
}
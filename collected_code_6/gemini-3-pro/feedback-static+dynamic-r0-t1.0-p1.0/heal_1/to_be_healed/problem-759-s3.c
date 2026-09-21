#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool isValidDecimalWithPrecision2(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int dotCount = 0;
    int dotIndex = -1;
    int signCount = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == '-' || str[i] == '+') {
            if (i != 0) {
                return false;
            }
            signCount++;
        } else if (str[i] == '.') {
            dotCount++;
            dotIndex = i;
            if (dotCount > 1) {
                return false;
            }
        } else if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }

    if (len == signCount || (dotCount == 1 && len - signCount == 1)) {
        return false;
    }

    if (dotCount == 1) {
        int fractionalDigits = len - 1 - dotIndex;
        if (fractionalDigits != 2) {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

int main(void) {
    const char *testCases[] = {
        "123.45",
        "-12.34",
        "0.00",
        ".50",
        "123",
        "123.4",
        "123.456",
        "abc",
        "",
        "+1.23"
    };
    
    size_t numTests = sizeof(testCases) / sizeof(testCases[0]);

    for (size_t i = 0; i < numTests; i++) {
        bool result = isValidDecimalWithPrecision2(testCases[i]);
        printf("\"%s\": %s\n", testCases[i], result ? "true" : "false");
    }

    return 0;
}
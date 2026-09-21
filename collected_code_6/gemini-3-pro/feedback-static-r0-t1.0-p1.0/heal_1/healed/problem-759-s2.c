#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool checkDecimalPrecision2(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    int len = 0;
    int dotCount = 0;
    int dotIndex = -1;

    while (str[len] != '\0') {
        if (str[len] == '.') {
            dotCount++;
            dotIndex = len;
        } else if (!isdigit((unsigned char)str[len]) && !(len == 0 && (str[len] == '-' || str[len] == '+'))) {
            return false;
        }
        len++;
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
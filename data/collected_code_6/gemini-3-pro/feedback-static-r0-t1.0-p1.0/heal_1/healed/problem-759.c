#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool checkDecimalPrecision2(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    int i = 0;

    if (str[i] == '-' || str[i] == '+') {
        i++;
    }

    bool has_digits_before_dot = false;
    while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
        has_digits_before_dot = true;
        i++;
    }

    if (str[i] == '\0') {
        return false;
    }

    if (str[i] == '.') {
        i++;
        int digits_after_dot = 0;
        while (str[i] != '\0' && isdigit((unsigned char)str[i])) {
            digits_after_dot++;
            i++;
        }
        
        if (str[i] == '\0' && digits_after_dot <= 2 && digits_after_dot > 0 && has_digits_before_dot) {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *testCases[] = {
        "12.34",
        "0.99",
        "-1.50",
        "+42.0",
        "123.",
        ".45",
        "12.345",
        "abc",
        NULL
    };

    size_t numTests = sizeof(testCases) / sizeof(testCases[0]);

    for (size_t i = 0; i < numTests; i++) {
        if (testCases[i] != NULL) {
            bool isValid = checkDecimalPrecision2(testCases[i]);
            printf("%s: %s\n", testCases[i], isValid ? "Valid" : "Invalid");
        }
    }

    return 0;
}
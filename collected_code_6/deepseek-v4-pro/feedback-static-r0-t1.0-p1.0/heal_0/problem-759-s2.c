#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int check_decimal_precision(const char *str, int precision) {
    if (str == NULL || precision < 0) {
        return 0;
    }

    const char *p = str;
    int digits_after_decimal = 0;
    int seen_digit = 0;
    int seen_decimal = 0;

    if (*p == '-' || *p == '+') {
        p++;
    }

    if (*p == '\0') {
        return 0;
    }

    while (*p != '\0') {
        if (*p == '.') {
            if (seen_decimal) {
                return 0;
            }
            seen_decimal = 1;
            p++;
            continue;
        }

        if (!isdigit((unsigned char)*p)) {
            return 0;
        }

        seen_digit = 1;

        if (seen_decimal) {
            digits_after_decimal++;
            if (digits_after_decimal > precision) {
                return 0;
            }
        }

        p++;
    }

    if (!seen_digit) {
        return 0;
    }

    if (seen_decimal && digits_after_decimal == 0) {
        return 0;
    }

    return 1;
}

int main(void) {
    const char *test_cases[] = {
        "123.45",
        "0.01",
        "-12.34",
        "+0.99",
        "100",
        "123.456",
        "abc.12",
        "12.",
        ".12",
        "12.3",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("%s => %d\n", test_cases[i], check_decimal_precision(test_cases[i], 2));
    }

    return 0;
}
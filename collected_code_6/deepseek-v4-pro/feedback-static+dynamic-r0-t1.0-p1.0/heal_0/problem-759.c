#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

typedef enum {
    DECIMAL_VALID,
    DECIMAL_INVALID_FORMAT,
    DECIMAL_INVALID_PRECISION
} DecimalCheckResult;

DecimalCheckResult check_decimal_precision_2(const char *str)
{
    if (str == NULL || *str == '\0') {
        return DECIMAL_INVALID_FORMAT;
    }

    const char *p = str;
    int decimal_points = 0;
    int digits_after_decimal = 0;
    int total_digits = 0;
    int leading_zeros = 0;
    bool has_digit_after_decimal = false;

    if (*p == '-' || *p == '+') {
        p++;
        if (*p == '\0') {
            return DECIMAL_INVALID_FORMAT;
        }
    }

    while (*p != '\0') {
        if (*p == '.') {
            decimal_points++;
            if (decimal_points > 1) {
                return DECIMAL_INVALID_FORMAT;
            }
            p++;
            while (*p != '\0') {
                if (!isdigit((unsigned char)*p)) {
                    return DECIMAL_INVALID_FORMAT;
                }
                digits_after_decimal++;
                has_digit_after_decimal = true;
                p++;
            }
            break;
        } else if (!isdigit((unsigned char)*p)) {
            return DECIMAL_INVALID_FORMAT;
        }

        if (*p == '0' && total_digits == 0 && leading_zeros == 0) {
            leading_zeros++;
        } else if (*p != '0' || leading_zeros > 0) {
            total_digits++;
        }

        p++;
    }

    if (decimal_points == 1 && !has_digit_after_decimal) {
        return DECIMAL_INVALID_FORMAT;
    }

    if (decimal_points == 1 && digits_after_decimal > 2) {
        return DECIMAL_INVALID_PRECISION;
    }

    if (decimal_points == 0) {
        return DECIMAL_INVALID_PRECISION;
    }

    if (digits_after_decimal == 0) {
        return DECIMAL_INVALID_PRECISION;
    }

    if (total_digits == 0 && digits_after_decimal == 0) {
        return DECIMAL_INVALID_FORMAT;
    }

    return DECIMAL_VALID;
}

int main(void)
{
    const char *test_values[] = {
        "123.45",
        "0.12",
        "1.2",
        "123.456",
        "12.",
        ".12",
        "123",
        "abc",
        "12.34.56",
        "-12.34",
        "+12.34",
        "12.345",
        "0.00",
        "00.12",
        "1.23",
        "12.3",
        ".",
        "",
        "12.a5",
        "-.12",
        "+.12",
        "12.",
        "12.0",
        "12.00",
        "0.0",
        "0.00",
        "000.12",
        "-0.12",
        "+0.12",
        "12.345"
    };

    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_tests; i++) {
        DecimalCheckResult result = check_decimal_precision_2(test_values[i]);
        printf("%-12s -> ", test_values[i]);
        switch (result) {
            case DECIMAL_VALID:
                printf("VALID\n");
                break;
            case DECIMAL_INVALID_FORMAT:
                printf("INVALID FORMAT\n");
                break;
            case DECIMAL_INVALID_PRECISION:
                printf("INVALID PRECISION\n");
                break;
            default:
                printf("UNKNOWN\n");
                break;
        }
    }

    return 0;
}
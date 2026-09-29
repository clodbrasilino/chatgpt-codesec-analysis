#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool check_decimal_precision_2(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    const char *p = str;
    bool has_digits = false;
    int decimal_places = 0;
    bool has_decimal_point = false;

    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '+' || *p == '-') {
        p++;
    }

    while (isdigit((unsigned char)*p)) {
        has_digits = true;
        p++;
    }

    if (*p == '.') {
        has_decimal_point = true;
        p++;
        while (isdigit((unsigned char)*p)) {
            decimal_places++;
            has_digits = true;
            p++;
        }
    }

    while (isspace((unsigned char)*p)) {
        p++;
    }

    if (*p != '\0' || !has_digits) {
        return false;
    }

    if (has_decimal_point && decimal_places <= 2) {
        return true;
    }

    if (!has_decimal_point) {
        return true;
    }

    return false;
}

int main(void) {
    const char *test_cases[] = {
        "123.45",
        "123.4",
        "123",
        "123.456",
        "-123.45",
        "+123.45",
        " 123.45 ",
        "123.",
        ".45",
        ".",
        "",
        "abc",
        "12.3.4",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("\"%s\" => %s\n", test_cases[i], 
               check_decimal_precision_2(test_cases[i]) ? "true" : "false");
    }

    return 0;
}
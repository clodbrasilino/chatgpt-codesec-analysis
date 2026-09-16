#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

bool is_integer(const char *str)
{
    if (str == NULL || *str == '\0') {
        return false;
    }

    size_t i = 0;
    if (str[i] == '-' || str[i] == '+') {
        i++;
        if (str[i] == '\0') {
            return false;
        }
    }

    long long value = 0;
    for (; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
        int digit = str[i] - '0';
        if (value > (LLONG_MAX - digit) / 10) {
            return false;
        }
        value = value * 10 + digit;
    }

    return true;
}

int main(void)
{
    const char *test_strings[] = {
        "123",
        "-456",
        "+789",
        "0",
        "abc",
        "12a",
        "",
        "-",
        "+",
        "  123",
        "123  ",
        "9999999999999999999999999999",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("\"%s\" -> %s\n", test_strings[i],
               is_integer(test_strings[i]) ? "integer" : "not integer");
    }

    return 0;
}
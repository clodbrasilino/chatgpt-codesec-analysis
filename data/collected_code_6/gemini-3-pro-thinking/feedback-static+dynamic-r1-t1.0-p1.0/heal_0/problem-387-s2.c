#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int check_hex_parity(const char *hex_string) {
    if (hex_string == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*hex_string)) {
        hex_string++;
    }

    if (hex_string[0] == '0' && (hex_string[1] == 'x' || hex_string[1] == 'X')) {
        hex_string += 2;
    }

    if (*hex_string == '\0') {
        return -1;
    }

    int last_digit = -1;

    while (*hex_string != '\0') {
        if (isspace((unsigned char)*hex_string)) {
            const char *tail = hex_string;
            while (isspace((unsigned char)*tail)) {
                tail++;
            }
            if (*tail != '\0') {
                return -1;
            }
            break;
        }

        if (!isxdigit((unsigned char)*hex_string)) {
            return -1;
        }

        last_digit = *hex_string;
        hex_string++;
    }

    if (last_digit == -1) {
        return -1;
    }

    last_digit = tolower((unsigned char)last_digit);

    if (last_digit == '0' || last_digit == '2' || last_digit == '4' ||
        last_digit == '6' || last_digit == '8' || last_digit == 'a' ||
        last_digit == 'c' || last_digit == 'e') {
        return 0;
    }

    return 1;
}

int main(void) {
    const char *test_cases[] = {
        "0x1A",
        "0X2B",
        "  123456789ABCDEF0  ",
        "0x",
        "invalid",
        NULL
    };

    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        int result = check_hex_parity(test_cases[i]);
        if (result == -1) {
            printf("Invalid\n");
        } else if (result == 0) {
            printf("Even\n");
        } else {
            printf("Odd\n");
        }
    }

    return 0;
}
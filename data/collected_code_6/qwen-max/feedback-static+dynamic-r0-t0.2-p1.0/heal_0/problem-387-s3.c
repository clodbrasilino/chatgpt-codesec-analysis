#include <stdio.h>
#include <stdbool.h>

bool is_hex_even(const char *hex) {
    while (*hex) {
        if (*hex >= '0' && *hex <= '9') {
            if ((*hex - '0') % 2 != 0) return false;
        } else if (*hex >= 'A' && *hex <= 'F') {
            if ((*hex - 'A' + 10) % 2 != 0) return false;
        } else if (*hex >= 'a' && *hex <= 'f') {
            if ((*hex - 'a' + 10) % 2 != 0) return false;
        } else {
            return false;
        }
        hex++;
    }
    return true;
}

int main() {
    const char *hex1 = "1A3B";
    const char *hex2 = "2C4E";

    if (is_hex_even(hex1)) {
        printf("%s is even\n", hex1);
    } else {
        printf("%s is odd\n", hex1);
    }

    if (is_hex_even(hex2)) {
        printf("%s is even\n", hex2);
    } else {
        printf("%s is odd\n", hex2);
    }

    return 0;
}
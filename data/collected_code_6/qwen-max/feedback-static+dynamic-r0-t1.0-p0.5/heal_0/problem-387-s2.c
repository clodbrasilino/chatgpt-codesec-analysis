#include <stdio.h>
#include <stdbool.h>

bool is_hex_even(const char *hex) {
    for (int i = 0; hex[i] != '\0'; ++i) {
        if (hex[i] >= '0' && hex[i] <= '9') {
            if ((hex[i] - '0') % 2 != 0) {
                return false;
            }
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            if ((hex[i] - 'a' + 10) % 2 != 0) {
                return false;
            }
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            if ((hex[i] - 'A' + 10) % 2 != 0) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    const char *hex1 = "1A3F";
    const char *hex2 = "2B4E";

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
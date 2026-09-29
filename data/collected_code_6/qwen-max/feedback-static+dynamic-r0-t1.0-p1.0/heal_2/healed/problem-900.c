#include <stdio.h>
#include <string.h>

int string_starts_with_number(const char *str, const char *number) {
    while (*number && *str && *number == *str) {
        number++;
        str++;
    }
    return *number == 0;
}

int main() {
    const char *str = "1234_start";
    const char *number = "1234";

    if (string_starts_with_number(str, number)) {
        printf("The string starts with the specified number.\n");
    } else {
        printf("The string does not start with the specified number.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str, size_t len) {
    char *write = str;
    for (size_t i = 0; i < len; i++) {
        if (!isdigit((unsigned char)str[i])) {
            *write++ = str[i];
        }
    }
    *write = '\0';
}

int main() {
    char strings[][20] = {"hello123", "world4567", "test890"};
    int num_strings = sizeof(strings) / sizeof(strings[0]);

    for (int i = 0; i < num_strings; i++) {
        remove_digits(strings[i], sizeof(strings[i]) - 1);
        printf("%s\n", strings[i]);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void remove_digits(char *str, size_t max_length) {
    char *write = str;
    char *read = str;
    while (*read != '\0' && (size_t)(read - str) < max_length) {
        if (!isdigit((unsigned char)*read)) {
            *write++ = *read;
            if ((size_t)(write - str) >= max_length - 1) {
                break;
            }
        }
        read++;
    }
    *write = '\0';
}

int main() {
    char strings[][20] = {"hello123", "world4567", "test890"};
    int num_strings = sizeof(strings) / sizeof(strings[0]);
    size_t max_length = sizeof(strings[0]);

    for (int i = 0; i < num_strings; i++) {
        remove_digits(strings[i], max_length - 1);
        printf("%s\n", strings[i]);
    }

    return 0;
}
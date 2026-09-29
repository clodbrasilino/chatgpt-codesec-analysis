#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

void reverse_strings_list(char **strings, int count) {
    for (int i = 0; i < count; ++i) {
        if (strings[i]) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(strings[i]);
            reverse_string(strings[i], len);
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "example", "test"};
    int count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_list(strings, count);

    for (int i = 0; i < count; ++i) {
        printf("%s\n", strings[i]);
    }

    return 0;
}
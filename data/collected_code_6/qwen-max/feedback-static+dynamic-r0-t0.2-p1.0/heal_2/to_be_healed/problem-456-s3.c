#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverse_strings_in_list(char **list, int size) {
    if (list == NULL || size <= 0) return;
    for (int i = 0; i < size; i++) {
        if (list[i] != NULL) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(list[i]);
            reverse_string(list[i], len);
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "C", "programming"};
    int size = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, size);

    for (int i = 0; i < size; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}
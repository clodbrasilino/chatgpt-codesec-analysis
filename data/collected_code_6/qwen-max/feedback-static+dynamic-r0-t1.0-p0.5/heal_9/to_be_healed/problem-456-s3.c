#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverse_strings_in_list(const char **list, int count) {
    if (list == NULL || count <= 0) {
        return;
    }
    for (int i = 0; i < count; i++) {
        if (list[i] != NULL && list[i][0] != '\0') {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len = strlen(list[i]);
            char *temp_str = malloc(len + 1);
            if (temp_str == NULL) {
                return;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp_str, list[i], len);
            temp_str[len] = '\0';
            reverse_string(temp_str, len);
            printf("%s\n", temp_str);
            free(temp_str);
        }
    }
}

int main() {
    const char *strings[] = {"hello", "world", "C", "programming"};
    int count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, count);

    return 0;
}
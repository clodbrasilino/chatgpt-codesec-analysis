#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t max_len) {
    if (str == NULL) {
        return;
    }
    size_t len = strnlen(str, max_len);
    if (len <= 1) {
        return;
    }
    size_t left = 0;
    size_t right = len - 1;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

void reverse_string_list(char **list, size_t count) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        if (list[i] != NULL) {
            reverse_string(list[i], 32);
        }
    }
}

int main(void) {
    const char *list[] = {
        "hello",
        "world",
        "C",
        "programming"
    };
    size_t count = sizeof(list) / sizeof(list[0]);

    for (size_t i = 0; i < count; i++) {
        char *buffer = strdup(list[i]);
        if (buffer == NULL) {
            continue;
        }
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        reverse_string(buffer, strlen(buffer));
        printf("%s\n", buffer);
        free(buffer);
    }

    return 0;
}
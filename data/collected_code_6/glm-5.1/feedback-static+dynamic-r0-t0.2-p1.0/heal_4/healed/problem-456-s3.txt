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
        char buffer[32];
        snprintf(buffer, sizeof(buffer), "%s", list[i]);
        if (buffer[sizeof(buffer) - 1] != '\0') {
            buffer[sizeof(buffer) - 1] = '\0';
        }
        reverse_string(buffer, sizeof(buffer));
        printf("%s\n", buffer);
    }

    return 0;
}
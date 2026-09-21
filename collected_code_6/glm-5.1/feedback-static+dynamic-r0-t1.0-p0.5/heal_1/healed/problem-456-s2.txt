#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    size_t len = strnlen(str, SIZE_MAX);
    if (len == 0 || len == SIZE_MAX) {
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
        reverse_string(list[i]);
    }
}

int main(void) {
    char *list[] = {
        strdup("hello"),
        strdup("world"),
        strdup("C"),
        strdup("programming")
    };
    size_t count = sizeof(list) / sizeof(list[0]);

    reverse_string_list(list, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }

    return 0;
}
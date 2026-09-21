#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t maxlen) {
    if (str == NULL) {
        return;
    }
    size_t len = strnlen(str, maxlen);
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

void reverse_string_list(char **list, size_t count, size_t maxlen) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        reverse_string(list[i], maxlen);
    }
}

int main(void) {
    char list[][12] = {
        "hello",
        "world",
        "C",
        "programming"
    };
    size_t count = sizeof(list) / sizeof(list[0]);
    size_t maxlen = sizeof(list[0]);

    reverse_string_list((char **)list, count, maxlen);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}
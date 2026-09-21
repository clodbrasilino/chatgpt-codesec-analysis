#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    char *end = strchr(str, '\0');
    if (end == str) {
        return;
    }
    end--;
    while (str < end) {
        char temp = *str;
        *str = *end;
        *end = temp;
        str++;
        end--;
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
    char list[][32] = {
        "hello",
        "world",
        "C",
        "programming"
    };
    size_t count = sizeof(list) / sizeof(list[0]);

    char *ptrs[sizeof(list) / sizeof(list[0])];
    for (size_t i = 0; i < count; i++) {
        ptrs[i] = list[i];
    }

    reverse_string_list(ptrs, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", ptrs[i]);
    }

    return 0;
}
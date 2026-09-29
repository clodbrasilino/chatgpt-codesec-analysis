#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    char *end = memchr(str, '\0', size);
    if (end == NULL) {
        end = str + size - 1;
    } else if (end == str) {
        return;
    } else {
        end--;
    }
    while (str < end) {
        char temp = *str;
        *str++ = *end;
        *end-- = temp;
    }
}

void reverse_string_list(char **list, const size_t *sizes, size_t count) {
    if (list == NULL || sizes == NULL || count == 0) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        reverse_string(list[i], sizes[i]);
    }
}

int main(void) {
    char strings[][12] = {
        "hello",
        "world",
        "C",
        "programming"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    char *list[4];
    size_t sizes[4];

    for (size_t i = 0; i < count; i++) {
        sizes[i] = strnlen(strings[i], sizeof(strings[i]));
        if (sizes[i] < sizeof(strings[i])) {
            sizes[i]++;
        }
        list[i] = strings[i];
    }

    reverse_string_list(list, sizes, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}
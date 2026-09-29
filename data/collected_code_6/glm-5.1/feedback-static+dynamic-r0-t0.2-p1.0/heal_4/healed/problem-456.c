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
        *str = *end;
        *end = temp;
        str++;
        end--;
    }
}

void reverse_string_list(char **list, const size_t *sizes, size_t count) {
    if (list == NULL || sizes == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        reverse_string(list[i], sizes[i]);
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
    size_t sizes[count];
    char *ptrs[count];
    for (size_t i = 0; i < count; i++) {
        sizes[i] = sizeof(list[i]);
        ptrs[i] = list[i];
    }
    reverse_string_list(ptrs, sizes, count);
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", ptrs[i]);
    }
    return 0;
}
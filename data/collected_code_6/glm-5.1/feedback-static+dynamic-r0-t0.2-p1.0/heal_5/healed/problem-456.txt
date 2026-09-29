#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }
    size_t len = strnlen(str, size);
    if (len == 0) {
        return;
    }
    char *start = str;
    char *end = str + len - 1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
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
    size_t *sizes = malloc(count * sizeof(*sizes));
    if (sizes == NULL) {
        return 1;
    }
    char **ptrs = malloc(count * sizeof(*ptrs));
    if (ptrs == NULL) {
        free(sizes);
        return 1;
    }
    for (size_t i = 0; i < count; i++) {
        sizes[i] = sizeof(list[i]);
        ptrs[i] = list[i];
    }
    reverse_string_list(ptrs, sizes, count);
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", ptrs[i]);
    }
    free(sizes);
    free(ptrs);
    return 0;
}
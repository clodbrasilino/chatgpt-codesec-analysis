#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t max_len) {
    if (str == NULL || max_len == 0) {
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

void reverse_string_list(char **list, size_t count, size_t max_str_len) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        reverse_string(list[i], max_str_len);
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
    size_t max_str_len = sizeof(list[0]);
    size_t ptrs_count = sizeof(list) / sizeof(list[0]);
    char **ptrs = malloc(ptrs_count * sizeof(char *));
    if (ptrs == NULL) {
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < ptrs_count; i++) {
        ptrs[i] = list[i];
    }
    
    reverse_string_list(ptrs, count, max_str_len);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", ptrs[i]);
    }

    free(ptrs);
    return 0;
}
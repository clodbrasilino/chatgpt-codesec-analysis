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
        if (list[i] != NULL) {
            reverse_string(list[i], max_str_len);
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
    size_t max_str_len = 0;
    for (size_t i = 0; i < count; i++) {
        size_t current_len = strnlen(list[i], SIZE_MAX);
        if (current_len > max_str_len) {
            max_str_len = current_len;
        }
    }
    
    char **buffer = malloc(count * sizeof(char *));
    if (buffer == NULL) {
        return 1;
    }
    for (size_t i = 0; i < count; i++) {
        buffer[i] = malloc(max_str_len + 1);
        if (buffer[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(buffer[j]);
            }
            free(buffer);
            return 1;
        }
        snprintf(buffer[i], max_str_len + 1, "%s", list[i]);
    }

    reverse_string_list(buffer, count, max_str_len);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", buffer[i]);
        free(buffer[i]);
    }
    free(buffer);

    return 0;
}
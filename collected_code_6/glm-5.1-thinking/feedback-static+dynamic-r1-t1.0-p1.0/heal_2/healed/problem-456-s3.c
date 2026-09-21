#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void reverse_string(char *str, size_t bufsize) {
    if (str == NULL || bufsize == 0) {
        return;
    }
    size_t len = strnlen(str, bufsize);
    size_t left = 0;
    size_t right = len > 0 ? len - 1 : 0;
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

void reverse_strings(char **strings, const size_t *sizes, size_t count) {
    if (strings == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        reverse_string(strings[i], sizes ? sizes[i] : 0);
    }
}

int main(void) {
    const char *original_strings[] = {"hello", "world", "C", "programming"};
    size_t count = sizeof(original_strings) / sizeof(original_strings[0]);
    char **strings = malloc(count * sizeof(char *));
    size_t *sizes = malloc(count * sizeof(size_t));
    if (strings == NULL || sizes == NULL) {
        free(strings);
        free(sizes);
        return EXIT_FAILURE;
    }
    size_t allocated_count = 0;
    for (size_t i = 0; i < count; i++) {
        sizes[i] = strnlen(original_strings[i], SIZE_MAX - 1) + 1;
        strings[i] = malloc(sizes[i]);
        if (strings[i] == NULL) {
            for (size_t j = 0; j < allocated_count; j++) {
                free(strings[j]);
            }
            free(strings);
            free(sizes);
            return EXIT_FAILURE;
        }
        snprintf(strings[i], sizes[i], "%s", original_strings[i]);
        allocated_count++;
    }
    reverse_strings(strings, sizes, count);
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }
    for (size_t i = 0; i < count; i++) {
        free(strings[i]);
    }
    free(strings);
    free(sizes);
    return EXIT_SUCCESS;
}
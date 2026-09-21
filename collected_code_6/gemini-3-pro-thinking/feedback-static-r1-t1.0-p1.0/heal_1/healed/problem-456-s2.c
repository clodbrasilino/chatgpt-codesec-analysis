#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 4096

int reverse_string_in_place(char *str);
int reverse_string_list(char **list, size_t count);
void free_string_list(char **list, size_t count);

int reverse_string_in_place(char *str) {
    if (!str) {
        return -1;
    }
    
    size_t len = strnlen(str, MAX_STRING_LEN);
    if (len == 0) {
        return 0;
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
    
    return 0;
}

int reverse_string_list(char **list, size_t count) {
    if (!list) {
        return -1;
    }
    
    for (size_t i = 0; i < count; i++) {
        if (!list[i]) {
            return -1;
        }
        if (reverse_string_in_place(list[i]) != 0) {
            return -1;
        }
    }
    
    return 0;
}

void free_string_list(char **list, size_t count) {
    if (!list) {
        return;
    }
    
    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *original_list[] = {"hello", "world", "developer", "C programming"};
    size_t count = sizeof(original_list) / sizeof(original_list[0]);

    char **mutable_list = malloc(count * sizeof(char *));
    if (!mutable_list) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        size_t len = strnlen(original_list[i], MAX_STRING_LEN);
        mutable_list[i] = malloc(len + 1);
        if (!mutable_list[i]) {
            free_string_list(mutable_list, i);
            return EXIT_FAILURE;
        }
        
        snprintf(mutable_list[i], len + 1, "%s", original_list[i]);
    }

    if (reverse_string_list(mutable_list, count) != 0) {
        free_string_list(mutable_list, count);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        if (printf("%s\n", mutable_list[i]) < 0) {
            free_string_list(mutable_list, count);
            return EXIT_FAILURE;
        }
    }

    free_string_list(mutable_list, count);
    return EXIT_SUCCESS;
}
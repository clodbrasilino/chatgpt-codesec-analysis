#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* extract_rear_index(const char** strings, size_t count) {
    if (strings == NULL || count == 0) {
        return NULL;
    }

    char* result = (char*)malloc(count * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            result[i] = '\0';
        } else {
            size_t len = strlen(strings[i]);
            if (len == 0) {
                result[i] = '\0';
            } else {
                result[i] = strings[i][len - 1];
            }
        }
    }

    return result;
}

int main(void) {
    const char* arr[] = {"hello", "world", "C", "", "testing"};
    size_t count = sizeof(arr) / sizeof(arr[0]);

    char* rear_chars = extract_rear_index(arr, count);
    if (rear_chars == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < count; i++) {
        if (rear_chars[i] != '\0') {
            printf("%c\n", rear_chars[i]);
        } else {
            printf("(empty string)\n");
        }
    }

    free(rear_chars);
    rear_chars = NULL;

    return 0;
}
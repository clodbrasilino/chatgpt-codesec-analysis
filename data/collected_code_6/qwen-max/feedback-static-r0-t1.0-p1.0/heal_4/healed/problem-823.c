#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool starts_with(const char *str, const char *prefix) {
    if (str == NULL || prefix == NULL) {
        return false;
    }
    while (*prefix && *str && *prefix == *str) {
        ++prefix;
        ++str;
    }
    return *prefix == '\0';
}

int main() {
    if (starts_with("hello world", "hello")) {
        printf("The string starts with the given substring.\n");
    } else {
        printf("The string does not start with the given substring.\n");
    }

    if (starts_with("hello world", "world")) {
        printf("The string starts with the given substring.\n");
    } else {
        printf("The string does not start with the given substring.\n");
    }

    return 0;
}
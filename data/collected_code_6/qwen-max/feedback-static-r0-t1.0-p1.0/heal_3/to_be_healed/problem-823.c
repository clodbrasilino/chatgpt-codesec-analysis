#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool starts_with(const char *str, const char *prefix) {
    if (str == NULL || prefix == NULL) {
        return false;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    return strncmp(str, prefix, strlen(prefix)) == 0;
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
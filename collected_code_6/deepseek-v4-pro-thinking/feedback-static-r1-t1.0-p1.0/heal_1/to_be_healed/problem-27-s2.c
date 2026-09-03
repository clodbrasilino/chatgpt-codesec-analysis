#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

void remove_digits(char *str) {
    if (str == NULL) {
        return;
    }

    char *src = str;
    char *dst = str;

    while (*src != '\0') {
        if (!isdigit((unsigned char)*src)) {
            *dst++ = *src;
        }
        src++;
    }

    *dst = '\0';
}

void remove_digits_from_list(char *strings[], size_t count) {
    if (strings == NULL) {
        return;
    }

    for (size_t i = 0; i < count; i++) {
        remove_digits(strings[i]);
    }
}

int main(void) {
    /* Possible weaknesses found:
     *  Variable 'storage' can be declared as const array [constVariable]
     */
    char storage[][20] = {
        "abc123def",
        "456",
        "abc",
        "12a34b56"
    };

    char *list[] = {
        storage[0],
        storage[1],
        storage[2],
        storage[3]
    };

    size_t count = sizeof(list) / sizeof(list[0]);

    remove_digits_from_list(list, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}
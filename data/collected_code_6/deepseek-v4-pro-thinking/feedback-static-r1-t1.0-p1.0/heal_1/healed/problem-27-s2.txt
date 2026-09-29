#include <stdio.h>
#include <stddef.h>
#include <ctype.h>
#include <string.h>

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
    const char storage[][20] = {
        "abc123def",
        "456",
        "abc",
        "12a34b56"
    };

    char buffers[][20] = {
        "",
        "",
        "",
        ""
    };

    char *list[] = {
        buffers[0],
        buffers[1],
        buffers[2],
        buffers[3]
    };

    size_t count = sizeof(list) / sizeof(list[0]);

    for (size_t i = 0; i < count; i++) {
        strcpy(buffers[i], storage[i]);
    }

    remove_digits_from_list(list, count);

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", list[i]);
    }

    return 0;
}
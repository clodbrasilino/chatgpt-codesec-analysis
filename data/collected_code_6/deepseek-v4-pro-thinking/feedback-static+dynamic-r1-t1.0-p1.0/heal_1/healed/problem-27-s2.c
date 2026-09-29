#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

void remove_digits(const char *str) {
    if (str == NULL) {
        return;
    }

    while (*str != '\0') {
        if (!isdigit((unsigned char)*str)) {
            putchar(*str);
        }
        str++;
    }
    putchar('\n');
}

void remove_digits_from_list(const char *strings[], size_t count) {
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

    const char *list[] = {
        storage[0],
        storage[1],
        storage[2],
        storage[3]
    };

    size_t count = sizeof(list) / sizeof(list[0]);

    remove_digits_from_list(list, count);

    return 0;
}
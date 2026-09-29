#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; ++i) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverse_strings_in_list(char **strings, size_t count) {
    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL) {
            size_t len = 0;
            while (strings[i][len] != '\0' && strings[i][len] != 0) {
                len++;
            }
            reverse_string(strings[i], len);
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "test", NULL};
    size_t count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, count);

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] != NULL) {
            printf("%s\n", strings[i]);
        }
    }

    return 0;
}
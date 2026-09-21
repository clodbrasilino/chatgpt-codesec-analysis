#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(const char *str, char *dest) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        dest[i] = str[len - i - 1];
        dest[len - i - 1] = temp;
    }
    for (size_t i = 0; i < len; i++) {
        dest[i] = str[i];
    }
    dest[len] = '\0';
}

void reverse_strings_in_list(char **list, int count) {
    if (list == NULL || count <= 0) return;
    for (int i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            char *reversed = malloc(len + 1);
            if (reversed != NULL) {
                reverse_string(list[i], reversed);
                free(list[i]);
                list[i] = reversed;
            }
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "C", "programming"};
    int count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    for (int i = 0; i < count; i++) {
        free(strings[i]);
    }

    return 0;
}
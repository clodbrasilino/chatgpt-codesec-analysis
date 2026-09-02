#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverse_strings_in_list(char **list, int size) {
    if (list == NULL || size <= 0) {
        return;
    }
    for (int i = 0; i < size; i++) {
        if (list[i] != NULL) {
            reverse_string(list[i]);
        }
    }
}

int main() {
    char *strings[] = {"hello", "world", "C", "programming"};
    int size = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, size);

    for (int i = 0; i < size; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void reverse_string(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void reverse_strings_in_list(const char **list, int count) {
    if (list == NULL || count <= 0) return;
    for (int i = 0; i < count; i++) {
        if (list[i] != NULL) {
            size_t len = strlen(list[i]);
            char *temp_str = malloc((len + 1) * sizeof(char));
            if (temp_str == NULL) {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            strcpy(temp_str, list[i]);
            reverse_string(temp_str, len);
            const char *original = list[i];
            *const_cast<char **>(&list[i]) = temp_str;
            free((void *)original);
        }
    }
}

int main() {
    const char *strings[] = {"hello", "world", "C", "programming"};
    int count = sizeof(strings) / sizeof(strings[0]);

    reverse_strings_in_list(strings, count);

    for (int i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }

    return 0;
}
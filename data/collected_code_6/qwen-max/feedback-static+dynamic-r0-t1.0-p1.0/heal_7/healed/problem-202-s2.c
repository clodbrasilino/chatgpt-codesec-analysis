#include <stdio.h>
#include <string.h>

void remove_even_characters(char *str, size_t str_len) {
    char temp[51] = {0};
    int j = 0;

    for (int i = 0; i < str_len && i < 50; i++) {
        if ((i + 1) % 2 != 0) {
            temp[j++] = str[i];
        }
    }

    temp[j] = '\0';
    memmove(str, temp, j + 1);
}

int main() {
    char str[51] = {0};
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';

        size_t str_len = strnlen(str, 51);
        remove_even_characters(str, str_len);
        printf("String after removing even characters: %s\n", str);
    }

    return 0;
}
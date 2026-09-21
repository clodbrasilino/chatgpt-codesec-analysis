#include <stdio.h>
#include <string.h>

void remove_even_characters(char *str, size_t len) {
    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        if ((i + 1) % 2 != 0 && j < len - 1) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[50];
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        size_t len = strnlen(str, sizeof(str));
        if (len > 0 && len < sizeof(str)) {
            remove_even_characters(str, len);
            printf("String after removing even characters: %s\n", str);
        } else {
            printf("Invalid input length. Please enter a shorter string.\n");
        }
    }
    return 0;
}
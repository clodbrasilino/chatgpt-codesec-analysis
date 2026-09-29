#include <stdio.h>
#include <string.h>

void remove_even_characters(char *str, size_t len) {
    char result[len];
    int j = 0;
    for (int i = 0; i < len && str[i] != '\0'; i++) {
        if ((i + 1) % 2 != 0) {
            if (j < (len - 1)) {
                result[j++] = str[i];
            }
        }
    }
    result[j] = '\0';
    memmove(str, result, strlen(result) + 1);
}

int main() {
    char str[50];
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        remove_even_characters(str, sizeof(str) - 1);
        printf("String after removing even characters: %s\n", str);
    }
    return 0;
}
#include <stdio.h>
#include <string.h>

void remove_even_characters(char *str) {
    char result[50] = "";
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((i + 1) % 2 != 0) {
            if (j < 49) {
                result[j++] = str[i];
            }
        }
    }
    result[j] = '\0';
    strcpy(str, result);
}

int main() {
    char str[50];
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        remove_even_characters(str);
        printf("String after removing even characters: %s\n", str);
    }
    return 0;
}
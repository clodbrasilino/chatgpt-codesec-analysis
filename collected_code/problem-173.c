#include <stdio.h>

void removeNonAlphanumeric(char* str) {
    if (str == NULL) {
        return;
    }
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (isalnum(str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    removeNonAlphanumeric(str);
    printf("String after removing non-alphanumeric characters: %s", str);
    return 0;
}
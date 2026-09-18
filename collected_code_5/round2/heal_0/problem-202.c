#include <stdio.h>
#include <string.h>

void removeEvenChars(char *str) {
    int i, j;
    int length = strlen(str);

    for(i = 0, j = 0; i < length; i++) {
        if (i % 2 != 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, 100, stdin);

    // Remove newline character, if present
    if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n')) {
        str[strlen (str) - 1] = '\0';
    }

    removeEvenChars(str);

    printf("Modified string: %s\n", str);

    return 0;
}
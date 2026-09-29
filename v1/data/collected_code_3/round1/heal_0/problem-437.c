#include <stdio.h>
#include <string.h>

void removeOddChars(char *str) {
    int i, j = 0, length;
    length = strlen(str);

    for(i = 0; i < length; i++) {
        if(i % 2 == 0) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    removeOddChars(str);

    printf("String after removing odd characters: %s\n", str);

    return 0;
}
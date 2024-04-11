#include <stdio.h>
#include <string.h>

void removeEvenChars(char* str) {
    int i, j = 0, length;
    char temp[100];

    length = strlen(str);

    for(i = 0; i < length; i++) {
        if(i % 2 != 0) {
            temp[j] = str[i];
            j++;
        }
    }
    temp[j] = '\0';

    strcpy(str, temp);
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    removeEvenChars(str);

    printf("String after removing even characters: %s\n", str);

    return 0;
}
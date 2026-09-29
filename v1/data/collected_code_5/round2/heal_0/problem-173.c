#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_non_alphanumeric(char *str) {
    int i = 0, j = 0;
    char temp[strlen(str) + 1];

    while (str[i]) {
        if (isalnum((unsigned char)str[i])) {
            temp[j++] = str[i];
        }
        i++;
    }

    temp[j] = '\0';
    strcpy(str, temp);
}

int main(void) {
    char str[] = "Hell@o, W0r!d";

    printf("Before: %s\n", str);
    remove_non_alphanumeric(str);
    printf("After: %s\n", str);

    return 0;
}
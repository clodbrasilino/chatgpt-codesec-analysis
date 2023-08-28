#include <stdio.h>

void splitString(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            printf("\n");
        } else {
            printf("%c", str[i]);
        }
    }
}

int main() {
    char str[] = "SplitThisString";
    splitString(str);
    return 0;
}
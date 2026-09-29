#include <stdio.h>
#include <stdbool.h>

void removeMultipleSpaces(char* str) {
    int i = 0, j = 0;
    bool spaceFound = false;

    while (str[i]) {
        if (str[i] != ' ') {
            str[j++] = str[i];
            spaceFound = false;
        }
        else if (str[i] == ' ' && !spaceFound) {
            str[j++] = str[i];
            spaceFound = true;
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "This   is  a    string  with   multiple   spaces";
    removeMultipleSpaces(str);
    printf("%s", str);
    return 0;
}
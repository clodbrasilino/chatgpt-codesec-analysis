#include <stdio.h>
#include <string.h>

void replaceMultipleOccurence(char* str) {
    int index = 0, i = 0;
    while (str[i]) {
        if (str[i] != str[i+1]) {
            str[index++] = str[i];
        }
        i++;
    }
    str[index] = '\0';
}

int main() {
    char str[] = "aaaabbbbcccddeee";
    replaceMultipleOccurence(str);
    printf("%s", str);
    return 0;
}
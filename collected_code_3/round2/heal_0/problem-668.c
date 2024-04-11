#include <stdio.h>
#include <string.h>

void replaceMultipleOccurrence(char* str, char ch) {
    int i = 0, j = 0;
    while (str[i]) {
        if (str[i] != ch || str[i+1] != ch) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int main() {
    char str[] = "aaaaabbbbcccdde";
    char ch = 'a';
    replaceMultipleOccurrence(str, ch);
    printf("%s\n", str);
    return 0;
}
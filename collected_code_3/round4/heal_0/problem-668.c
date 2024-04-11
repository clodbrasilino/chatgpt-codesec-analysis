#include <stdio.h>
#include <string.h>

void replaceMultipleOccurrence(char* str, char ch) {
    int n = strlen(str);
    int j = 0;
    for (int i = 1; i < n; i++) {
        if (str[j] == ch && str[i] == ch) {
            continue;
        }
        j++;
        str[j] = str[i];
    }
    str[j + 1] = '\0';
}

int main() {
    char str[] = "aaaabbbbccccc";
    char ch = 'a';
    replaceMultipleOccurrence(str, ch);
    printf("%s\n", str);
    return 0;
}
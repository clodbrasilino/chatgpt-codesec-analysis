#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isVowel(char ch) {
    ch = tolower(ch);
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
}

void reverseVowels(char *str) {
    if(str == NULL) return;
    int length = strlen(str);
    if(length == 0) return;

    int i = 0, j = length - 1;
    while (i < j) {
        if (!isVowel(str[i])) {
            i++;
            continue;
        }
        if (!isVowel(str[j])) {
            j--;
            continue;
        }
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

int main() {
    char str[100] = {0};

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);

    if(str[strlen(str)-1] == '\n') {
        str[strlen(str)-1] = '\0';
    }

    reverseVowels(str);
    printf("Reversed string: %s\n", str);
    return 0;
}
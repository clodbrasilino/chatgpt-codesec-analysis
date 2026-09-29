#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define STRING_SIZE 100

int isVowel(char ch) {
    ch = tolower(ch);
    return (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u');
}

void reverseVowels(char *str, int length) {
    if(!str || length <= 0) return;
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
    char str[STRING_SIZE];

    printf("Enter a string: ");
    if(fgets(str, STRING_SIZE, stdin) != NULL){
        int length = strnlen(str, STRING_SIZE);
        if(length > 0 && str[length-1] == '\n') {
            str[length-1] = '\0';
            length--; 
        }

        reverseVowels(str, length);
        printf("Reversed string: %s\n", str);
    }

    return 0;
}
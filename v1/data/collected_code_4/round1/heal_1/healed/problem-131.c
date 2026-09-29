#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isVowel(char c) {
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void reverseVowels(char* s) {
    int i = 0, j = strlen(s) - 1;
    while (i < j) {
        if (!isVowel(s[i])) {
            i++;
            continue;
        }
        if (!isVowel(s[j])) {
            j--;
            continue;
        }
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
}

int main() {
    char str[] = "Hello, World!";
    printf("Original string: %s\n", str);
    reverseVowels(str);
    printf("Reversed vowels: %s\n", str);
    return 0;
}
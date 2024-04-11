#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isVowel(char c) {
    return (c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U');
}

void reverseVowels(char* str) {
    int i = 0, j = strlen(str) - 1;
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
    char str[] = "Hello, World!";
    reverseVowels(str);
    printf("%s\n", str);
    return 0;
}
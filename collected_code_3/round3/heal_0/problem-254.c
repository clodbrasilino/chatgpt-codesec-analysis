#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findWords(char* str) {
    char* word = strtok(str, " ");
    while (word != NULL) {
        if (tolower(word[0]) == 'a' || tolower(word[0]) == 'e') {
            printf("%s\n", word);
        }
        word = strtok(NULL, " ");
    }
}

int main() {
    char str[] = "Apple banana Elephant cat dog Ant Eel fish";
    findWords(str);
    return 0;
}
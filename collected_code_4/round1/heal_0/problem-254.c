#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

void findWords(char* str) {
    char word[MAX_WORD_LENGTH];
    int index = 0;
    int i;
    for (i = 0; i <= strlen(str); i++ ) {
        if (isspace(str[i]) || str[i] == '\0') {
            word[index] = '\0';
            if (index > 0 && (word[0] == 'a' || word[0] == 'e' || word[0] == 'A' || word[0] == 'E')) {
                printf("%s\n", word);
            }
            index = 0;
        } else if (index < MAX_WORD_LENGTH - 1) {
            word[index++] = str[i];
        }
    }
}

int main() {
    char str[] = "a quick brown fox jumps over the lazy dog";
    findWords(str);
    return 0;
}
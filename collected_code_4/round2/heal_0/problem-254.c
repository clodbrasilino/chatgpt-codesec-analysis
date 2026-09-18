#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkWord(char *word) {
    if(word[0] == 'a' || word[0] == 'e') {
        return 1;
    }
    return 0;
}

void findWords(char *str) {
    char *token = strtok(str, " ");
  
    while (token != NULL) {
        if(checkWord(token)) {
            printf("%s\n", token);
        }
        token = strtok(NULL, " ");
    }
}

int main() {
    char str[] = "apple banana are easy to eat";
 
    findWords(str);

    return 0;
}
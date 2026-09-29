#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void findAdverbs(char* sentence) {
    char* word;
    int position = 0;

    word = strtok(sentence, " ");
    while(word != NULL) {
        int len = strlen(word);
        if(len > 2 && word[len-2] == 'l' && word[len-1] == 'y') {
            printf("Adverb: %s, Position: %d\n", word, position);
        }
        word = strtok(NULL, " ");
        position++;
    }
}

int main() {
    char sentence[100];
    printf("Enter a sentence: ");
    fgets(sentence, 100, stdin);
    sentence[strcspn(sentence, "\n")] = 0;
    findAdverbs(sentence);
    return 0;
}
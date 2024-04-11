#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 20

void find_adverbs(char* sentence) {
    char* words[MAX_WORDS];
    int word_count = 0;
    char* word = strtok(sentence, " ");
    while (word != NULL) {
        words[word_count] = malloc(strlen(word) + 1);
        strcpy(words[word_count], word);
        word_count++;
        word = strtok(NULL, " ");
    }

    for (int i = 0; i < word_count; i++) {
        int len = strlen(words[i]);
        if (len > 2 && words[i][len - 2] == 'l' && words[i][len - 1] == 'y') {
            printf("Adverb: %s, Position: %d\n", words[i], i + 1);
        }
        free(words[i]);
    }
}

int main() {
    char sentence[] = "He quickly ran to the beautifully decorated house.";
    find_adverbs(sentence);
    return 0;
}
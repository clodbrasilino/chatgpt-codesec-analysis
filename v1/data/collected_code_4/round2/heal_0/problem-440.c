#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 20

char *adverbs[MAX_WORDS];
int positions[MAX_WORDS];

int isAdverb(const char* word) {
    size_t len = strlen(word);
    if(len < 2) {
        return 0;
    }
    return strcmp(word + len - 2, "ly") == 0;
}

void findAdverbs(char *sentence, char **adverbs, int *positions, int *count) {
    char *word;
    int pos = 0;
    word = strtok(sentence, " ");

    while(word != NULL && *count < MAX_WORDS) {
        if(isAdverb(word)) {
            adverbs[*count] = (char*) malloc((strlen(word) + 1) * sizeof(char));
            if (adverbs[*count] != NULL) {
                strcpy(adverbs[*count], word);
                positions[*count] = pos;
                (*count)++;
            } else {
                return;
            }
        }

        word = strtok(NULL, " ");
        pos++;
    }
}

int main() {
    char sentence[200];
    int count = 0;

    printf("Enter a sentence: ");
    fgets(sentence, 200, stdin);

    findAdverbs(sentence, adverbs, positions, &count);

    for(int i = 0; i < count; i++) {
        printf("Found adverb '%s' at position %d\n", adverbs[i], positions[i]);
        free(adverbs[i]);
    }

    return 0;
}
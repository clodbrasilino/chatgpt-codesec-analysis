#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 100

char* findFirstRepeatedWord(char *sentence){
    char *result = NULL;

    char *words[MAX_WORDS];
    int cnt = 0;

    char *word = strtok(sentence, " ");
    while(word) {
        for(int i = 0; i < cnt; i++){
            if(strcmp(words[i], word) == 0){
                result = words[i];
                return result;
            }
        }
        words[cnt] = word;
        cnt++;
        word = strtok(NULL, " ");
    }

    return result;
}

int main() {
    char sentence[] = "This is a test. This is only a test.";

    char *result = findFirstRepeatedWord(sentence);
    if(result != NULL) {
        printf("First repeated word: %s\n", result);
    } else {
        printf("No repeated words\n");
    }

    return 0;
}
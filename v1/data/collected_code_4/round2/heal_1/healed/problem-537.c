#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 100

char* findFirstRepeatedWord(char* str) {
    char* words[MAX_WORDS];
    char* word;
    int i, no_of_words = 0;
    char* repeated_word = NULL;

    word = strtok(str, " ");

    while(word) {
        for(i=0; i<no_of_words; i++) {
            if(strcmp(words[i], word) == 0) {
                repeated_word = malloc(strlen(words[i])+1);
                strcpy(repeated_word, words[i]);
                goto CLEANUP;
            }
        }
        words[no_of_words] = malloc(strlen(word)+1);
        if(words[no_of_words] == NULL) {
            printf("Error: Unable to allocate memory\n");
            exit(1);
        }
        strcpy(words[no_of_words], word);
        no_of_words++;
        word = strtok(NULL, " ");
    }

CLEANUP:
    for(i=0; i<no_of_words; i++) {
        free(words[i]);
    }

    return repeated_word;
}

int main() {
    char str[] = "This is a test string for the function to find the first repeated word.";
    char* repeated_word = findFirstRepeatedWord(str);

    if(repeated_word) {
        printf("First repeated word found: %s\n", repeated_word);  
        free(repeated_word);      
    } else {
        printf("No repeated word found\n");
    }

    return 0;
}
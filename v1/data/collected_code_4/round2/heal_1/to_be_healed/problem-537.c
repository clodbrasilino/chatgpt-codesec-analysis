#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 100

char* findFirstRepeatedWord(char* str) {
    char* words[MAX_WORDS];
    char* word;
    int i, no_of_words = 0;

    word = strtok(str, " ");

    while(word) {
        for(i=0; i<no_of_words; i++) {
            if(strcmp(words[i], word) == 0) {
                return word;
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

    for(i=0; i<no_of_words; i++) {
        free(words[i]);
    }

    return NULL;
/* Possible weaknesses found:
 *  leak of 'words[2]' [CWE-401] [-Wanalyzer-malloc-leak]
 *  leak of 'words[3]' [CWE-401] [-Wanalyzer-malloc-leak]
 *  leak of 'words[1]' [CWE-401] [-Wanalyzer-malloc-leak]
 *  leak of 'words[0]' [CWE-401] [-Wanalyzer-malloc-leak]
 */
}

int main() {
    char str[] = "This is a test string for the function to find the first repeated word.";
    char* repeated_word = findFirstRepeatedWord(str);

    if(repeated_word) {
        printf("First repeated word found: %s\n", repeated_word);
    } else {
        printf("No repeated word found\n");
    }

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORD_LEN 100

char* findFirstRepeatedWord(char* str) {
    char* word = (char*)malloc(MAX_WORD_LEN);
    char* words[100];
    int i, j = 0, k = 0, w = 0;

    for(i = 0; i <= strlen(str); i++) {
        if(str[i] == ' ' || str[i] == '\0') {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'word' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            word[j] = '\0';
            for(k = 0; k < w; k++) {
                if(strcmp(words[k], word) == 0) {
                    return word;
                }
            }
            words[w] = (char*)malloc(strlen(word) + 1);
            strcpy(words[w], word);
            w++;
            j = 0;
        } else {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'word' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            word[j++] = str[i];
        }
    }
    return NULL;
/* Possible weaknesses found:
 *  leak of 'words[0]' [CWE-401] [-Wanalyzer-malloc-leak]
 */
}

int main() {
    char str[] = "This is a test string for testing";
    char* word = findFirstRepeatedWord(str);
    if(word != NULL) {
        printf("First repeated word: %s\n", word);
    } else {
        printf("No repeated words found\n");
    }
    return 0;
}
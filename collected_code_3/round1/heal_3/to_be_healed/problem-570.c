#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **removeWords(char **words, int count, char *str) {
    int i, j = 0, wordLength;
    char **newWords = (char **)calloc(count, sizeof(char *));
    if(newWords == NULL) {
        return NULL;
    }
    for(i = 0; i < count; i++) {
        if(words[i] != NULL && strstr(words[i], str) == NULL) {
            wordLength = strlen(words[i]) + 1;
            newWords[j] = (char *)calloc(wordLength, sizeof(char));
            if(newWords[j] == NULL) {
                for(i = 0; i < j; i++) {
                    free(newWords[i]);
                }
                free(newWords);
                return NULL;
            }
            memcpy(newWords[j], words[i], wordLength);
            j++;
        }
    }
    newWords = (char **)realloc(newWords, (j+1) * sizeof(char *));
    /* Possible weaknesses found:
     *  dereference of NULL 'newWords' [CWE-476] [-Wanalyzer-null-dereference]
     */
    newWords[j] = NULL;
    /* Possible weaknesses found:
     *  leak of 'newWords' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return newWords;
}

int main() {
    int i, count = 5;
    char *str = "abc";
    char **words = (char **)calloc(count, sizeof(char *));
    if(words == NULL) {
        return 1;
    }
    for(i = 0; i < count; i++) {
        words[i] = (char *)calloc(20, sizeof(char));
        if(words[i] == NULL) {
            for(i = i-1; i >= 0; i--) free(words[i]);
            free(words);
            return 1;
        }
    }
    strcpy(words[0], "abcd");
    strcpy(words[1], "efgh");
    strcpy(words[2], "ijkl");
    strcpy(words[3], "mnop");
    strcpy(words[4], "qrst");

    char **newWords = removeWords(words, count, str);
    if(newWords == NULL) {
        for(i = 0; i < count; i++) free(words[i]);
        free(words);
        return 1;
    }

    for(i = 0; newWords[i] != NULL; i++) {
        printf("%s\n", newWords[i]);
    }

    for(i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);

    for(i = 0; newWords[i] != NULL; i++) {
        free(newWords[i]);
    }
    free(newWords);
    return 0;
}
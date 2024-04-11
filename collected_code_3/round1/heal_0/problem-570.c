#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **removeWords(char **words, int count, char *str) {
    int i, j = 0;
    char **newWords = (char **)malloc(count * sizeof(char *));
    for(i = 0; i < count; i++) {
        if(strstr(words[i], str) == NULL) {
            newWords[j] = (char *)malloc((strlen(words[i]) + 1) * sizeof(char));
            strcpy(newWords[j], words[i]);
            j++;
        }
    }
    newWords = (char **)realloc(newWords, j * sizeof(char *));
    return newWords;
}

int main() {
    int i, count = 5;
    char *str = "abc";
    char **words = (char **)malloc(count * sizeof(char *));
    for(i = 0; i < count; i++) {
        words[i] = (char *)malloc(20 * sizeof(char));
    }
    strcpy(words[0], "abcd");
    strcpy(words[1], "efgh");
    strcpy(words[2], "ijkl");
    strcpy(words[3], "mnop");
    strcpy(words[4], "qrst");

    char **newWords = removeWords(words, count, str);
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
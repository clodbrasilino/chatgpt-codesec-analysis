#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **removeWords(char **words, int count, char *str) {
    int i, j = 0;
    char **newWords = (char **)calloc(count, sizeof(char *));
    if(newWords == NULL) {
        return NULL;
    }
    for(i = 0; i < count; i++) {
        if(words[i] != NULL && strstr(words[i], str) == NULL) {
            newWords[j] = (char *)calloc(strlen(words[i]) + 1, sizeof(char));
            if(newWords[j] != NULL) {
                strcpy(newWords[j], words[i]);
                j++;
            }
        }
    }
    newWords = (char **)realloc(newWords, j * sizeof(char *));
    /* Possible weaknesses found:
     *  leak of 'newWords' [CWE-401] [-Wanalyzer-malloc-leak]
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
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
        return 1;
    }
    /* Possible weaknesses found:
     *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
     *  read of 8 bytes from after the end of the region
     *  use of uninitialized value '*newWords_75 + _38' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     */
    for(i = 0; newWords[i] != NULL; i++) {
        printf("%s\n", newWords[i]);
    }

    for(i = 0; i < count; i++) {
        free(words[i]);
    }
    free(words);

    /* Possible weaknesses found:
     *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
     *  read of 8 bytes from after the end of the region
     */
    for(i = 0; newWords[i] != NULL; i++) {
        free(newWords[i]);
    }
    free(newWords);
    return 0;
}
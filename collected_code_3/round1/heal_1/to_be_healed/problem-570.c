#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **removeWords(char **words, int count, char *str) {
    int i, j = 0;
    char **newWords = (char **)malloc(count * sizeof(char *));
    for(i = 0; i < count; i++) {
        if(strstr(words[i], str) == NULL) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'newWords' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            newWords[j] = (char *)malloc((strlen(words[i]) + 1) * sizeof(char));
            strcpy(newWords[j], words[i]);
            j++;
        }
    }
    newWords = (char **)realloc(newWords, j * sizeof(char *));
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     *  leak of 'newWords' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    return newWords;
}

int main() {
    int i, count = 5;
    char *str = "abc";
    char **words = (char **)malloc(count * sizeof(char *));
    for(i = 0; i < count; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL 'words' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        words[i] = (char *)malloc(20 * sizeof(char));
    }
    strcpy(words[0], "abcd");
    strcpy(words[1], "efgh");
    strcpy(words[2], "ijkl");
    strcpy(words[3], "mnop");
    strcpy(words[4], "qrst");

    char **newWords = removeWords(words, count, str);
    /* Possible weaknesses found:
     *  heap-based buffer over-read [CWE-126] [-Wanalyzer-out-of-bounds]
     *  use of uninitialized value '*newWords_70 + _35' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     *  dereference of NULL 'newWords' [CWE-476] [-Wanalyzer-null-dereference]
     *  read of 8 bytes from after the end of the region
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
     *  use of uninitialized value '*newWords_70 + _47' [CWE-457] [-Wanalyzer-use-of-uninitialized-value]
     *  read of 8 bytes from after the end of the region
     */
    for(i = 0; newWords[i] != NULL; i++) {
        free(newWords[i]);
    }
    free(newWords);
    return 0;
}
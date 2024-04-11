#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **getLongWords(char **words, int wordCount, int n, int *resultCount) {
    char **longWords = (char **)malloc(sizeof(char *) * wordCount);
    if (longWords == NULL) {
        *resultCount = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < wordCount; i++) {
        if (strlen(words[i]) > n) {
            longWords[count] = words[i];
            count++;
        }
    }

    *resultCount = count;
    return longWords;
}

int main() {
    char *words[] = {"apple", "banana", "cherry", "date", "elderberry"};
    int wordCount = sizeof(words) / sizeof(words[0]);
    int n = 5;
    int resultCount;

    char **longWords = getLongWords(words, wordCount, n, &resultCount);
    if (longWords == NULL) {
        return 1;
    }

    for (int i = 0; i < resultCount; i++) {
        printf("%s\n", longWords[i]);
    }

    free(longWords);

    return 0;
}
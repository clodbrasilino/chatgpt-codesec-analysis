#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define MAX_WORDS 10000

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

int findWordIndex(WordCount words[], int numWords, const char *word) {
    int i;
    for (i = 0; i < numWords; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

void toLowerCase(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int compareWordCounts(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    return wb->count - wa->count;
}

int countMostCommonWords(const char *filename, WordCount words[], int maxWords, int topN) {
    FILE *file = NULL;
    char buffer[MAX_WORD_LEN];
    int numWords = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'j' can be reduced. [variableScope]
     */
    int i, j;

    if (filename == NULL || words == NULL || maxWords <= 0 || topN <= 0) {
        return -1;
    }

    file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    while (fscanf(file, "%99s", buffer) == 1) {
        toLowerCase(buffer);
        
        j = 0;
        for (i = 0; buffer[i] != '\0' && j < MAX_WORD_LEN - 1; i++) {
            if (isalpha((unsigned char)buffer[i])) {
                buffer[j++] = buffer[i];
            }
        }
        buffer[j] = '\0';

        if (j == 0) {
            continue;
        }

        int index = findWordIndex(words, numWords, buffer);
        if (index >= 0) {
            words[index].count++;
        } else if (numWords < maxWords) {
            strncpy(words[numWords].word, buffer, MAX_WORD_LEN - 1);
            words[numWords].word[MAX_WORD_LEN - 1] = '\0';
            words[numWords].count = 1;
            numWords++;
        }
    }

    if (fclose(file) != 0) {
        return -1;
    }

    qsort(words, numWords, sizeof(WordCount), compareWordCounts);

    return numWords < topN ? numWords : topN;
}

int main(void) {
    WordCount words[MAX_WORDS];
    const char *filename = "dictionary.txt";
    int topN = 10;
    int result;
    int i;

    result = countMostCommonWords(filename, words, MAX_WORDS, topN);
    
    if (result < 0) {
        fprintf(stderr, "Error: Could not process file %s\n", filename);
        return EXIT_FAILURE;
    }

    printf("Top %d most common words:\n", result);
    for (i = 0; i < result; i++) {
        printf("%d. %s: %d\n", i + 1, words[i].word, words[i].count);
    }

    return EXIT_SUCCESS;
}
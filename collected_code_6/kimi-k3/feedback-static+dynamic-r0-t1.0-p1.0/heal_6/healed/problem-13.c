#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 100

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

void toLowerCase(char *str) {
    if (str == NULL) return;
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int findWord(WordCount *words, int count, const char *word) {
    if (words == NULL || word == NULL) return -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

int compareWordCount(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wb->count > wa->count) return 1;
    if (wb->count < wa->count) return -1;
    return 0;
}

int addWord(WordCount *words, int *wordCount, int maxWords, const char *buffer) {
    if (words == NULL || wordCount == NULL || buffer == NULL) return 0;
    
    int index = findWord(words, *wordCount, buffer);
    if (index >= 0) {
        words[index].count++;
        return 1;
    } else if (*wordCount < maxWords) {
        size_t len = strnlen(buffer, MAX_WORD_LEN - 1);
        strncpy(words[*wordCount].word, buffer, len);
        words[*wordCount].word[len] = '\0';
        words[*wordCount].count = 1;
        (*wordCount)++;
        return 1;
    }
    return 0;
}

int countWords(const char *text, WordCount *words, int maxWords) {
    if (text == NULL || words == NULL || maxWords <= 0) return 0;
    
    char buffer[MAX_WORD_LEN];
    int wordCount = 0;
    size_t bufIndex = 0;
    
    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            if (bufIndex < sizeof(buffer) - 1) {
                buffer[bufIndex++] = text[i];
            }
        } else {
            if (bufIndex > 0) {
                buffer[bufIndex] = '\0';
                toLowerCase(buffer);
                addWord(words, &wordCount, maxWords, buffer);
                bufIndex = 0;
            }
        }
    }
    
    if (bufIndex > 0) {
        buffer[bufIndex] = '\0';
        toLowerCase(buffer);
        addWord(words, &wordCount, maxWords, buffer);
    }
    
    return wordCount;
}

void printMostCommonWords(WordCount *words, int count, int topN) {
    if (words == NULL || count <= 0 || topN <= 0) return;
    
    qsort(words, count, sizeof(WordCount), compareWordCount);
    
    int limit = (topN < count) ? topN : count;
    for (int i = 0; i < limit; i++) {
        printf("%s: %d\n", words[i].word, words[i].count);
    }
}

int main(void) {
    const char *dictionary = "the quick brown fox jumps over the lazy dog the fox is quick and the dog is lazy";
    
    WordCount *words = malloc(MAX_WORDS * sizeof(WordCount));
    if (words == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    memset(words, 0, MAX_WORDS * sizeof(WordCount));
    
    int wordCount = countWords(dictionary, words, MAX_WORDS);
    
    if (wordCount > 0) {
        printf("Most common words:\n");
        printMostCommonWords(words, wordCount, 10);
    } else {
        printf("No words found.\n");
    }
    
    free(words);
    words = NULL;
    
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_WORD_LEN 100
#define INITIAL_CAPACITY 1000
#define MAX_INPUT_LEN (10 * 1024 * 1024)

typedef struct {
    char *word;
    int count;
} WordCount;

typedef struct {
    WordCount *words;
    size_t size;
    size_t capacity;
} WordList;

int initWordList(WordList *list) {
    if (list == NULL) {
        return 0;
    }
    list->words = calloc(INITIAL_CAPACITY, sizeof(WordCount));
    if (list->words == NULL) {
        return 0;
    }
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return 1;
}

void freeWordList(WordList *list) {
    if (list != NULL) {
        if (list->words != NULL) {
            for (size_t i = 0; i < list->size; i++) {
                free(list->words[i].word);
            }
            free(list->words);
        }
        list->words = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int resizeWordList(WordList *list) {
    if (list == NULL || list->capacity == 0) {
        return 0;
    }
    if (list->capacity > SIZE_MAX / 2) {
        return 0;
    }
    size_t newCapacity = list->capacity * 2;
    if (newCapacity > SIZE_MAX / sizeof(WordCount)) {
        return 0;
    }
    WordCount *newWords = realloc(list->words, newCapacity * sizeof(WordCount));
    if (newWords == NULL) {
        return 0;
    }
    for (size_t i = list->capacity; i < newCapacity; i++) {
        newWords[i].word = NULL;
        newWords[i].count = 0;
    }
    list->words = newWords;
    list->capacity = newCapacity;
    return 1;
}

void toLowerCase(char *str) {
    if (str == NULL) {
        return;
    }
    for (size_t i = 0; str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int findWord(const WordList *list, const char *word) {
    if (list == NULL || word == NULL || list->words == NULL) {
        return -1;
    }
    for (size_t i = 0; i < list->size; i++) {
        if (list->words[i].word != NULL && strcmp(list->words[i].word, word) == 0) {
            if (i > INT_MAX) {
                return -1;
            }
            return (int)i;
        }
    }
    return -1;
}

int addWord(WordList *list, const char *word) {
    if (list == NULL || word == NULL || list->words == NULL) {
        return 0;
    }
    
    size_t wordLen = strnlen(word, MAX_WORD_LEN);
    if (wordLen == 0 || wordLen >= MAX_WORD_LEN) {
        return 0;
    }

    int index = findWord(list, word);
    if (index >= 0) {
        if (list->words[index].count < INT_MAX) {
            list->words[index].count++;
        }
        return 1;
    }

    if (list->size >= list->capacity) {
        if (!resizeWordList(list)) {
            return 0;
        }
    }

    char *newWord = malloc(wordLen + 1);
    if (newWord == NULL) {
        return 0;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(newWord, word, wordLen);
    newWord[wordLen] = '\0';
    
    list->words[list->size].word = newWord;
    list->words[list->size].count = 1;
    list->size++;
    return 1;
}

int compareWordCount(const void *a, const void *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    
    if (wb->count != wa->count) {
        return (wb->count > wa->count) ? 1 : -1;
    }
    if (wa->word == NULL && wb->word == NULL) {
        return 0;
    }
    if (wa->word == NULL) {
        return 1;
    }
    if (wb->word == NULL) {
        return -1;
    }
    return strcmp(wa->word, wb->word);
}

int processText(WordList *list, const char *text) {
    if (list == NULL || text == NULL) {
        return 0;
    }

    size_t textLen = strnlen(text, MAX_INPUT_LEN);
    if (textLen == 0 || textLen >= MAX_INPUT_LEN) {
        return 0;
    }

    char *buffer = malloc(MAX_WORD_LEN);
    if (buffer == NULL) {
        return 0;
    }
    
    size_t bufIndex = 0;
    int result = 1;
    
    for (size_t i = 0; i < textLen; i++) {
        unsigned char c = (unsigned char)text[i];
        
        if (isalnum(c) || c == '\'') {
            if (bufIndex < MAX_WORD_LEN - 1) {
                buffer[bufIndex++] = (char)c;
            }
        } else {
            if (bufIndex > 0) {
                buffer[bufIndex] = '\0';
                toLowerCase(buffer);
                if (!addWord(list, buffer)) {
                    result = 0;
                    break;
                }
                bufIndex = 0;
            }
        }
    }
    
    if (result && bufIndex > 0) {
        buffer[bufIndex] = '\0';
        toLowerCase(buffer);
        if (!addWord(list, buffer)) {
            result = 0;
        }
    }
    
    free(buffer);
    return result;
}

void findMostCommonWords(const char *text, int n) {
    if (text == NULL || n <= 0) {
        fprintf(stderr, "Invalid input parameters\n");
        return;
    }

    WordList list = {0};
    if (!initWordList(&list)) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    if (!processText(&list, text)) {
        fprintf(stderr, "Error processing text\n");
        freeWordList(&list);
        return;
    }

    if (list.size == 0) {
        printf("No words found in text\n");
        freeWordList(&list);
        return;
    }

    qsort(list.words, list.size, sizeof(WordCount), compareWordCount);

    size_t displayCount = ((size_t)n < list.size) ? (size_t)n : list.size;
    
    printf("Top %d most common words:\n", n);
    for (size_t i = 0; i < displayCount; i++) {
        printf("%zu. %s: %d\n", i + 1, list.words[i].word, list.words[i].count);
    }

    freeWordList(&list);
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. "
                      "The dog was really lazy. The fox was very quick and brown. "
                      "The lazy dog could not catch the quick brown fox.";
    
    int n = 5;
    
    findMostCommonWords(text, n);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 100
#define INITIAL_CAPACITY 1000

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordCount;

typedef struct {
    WordCount *words;
    size_t size;
    size_t capacity;
} WordList;

int initWordList(WordList *list) {
    list->words = malloc(INITIAL_CAPACITY * sizeof(WordCount));
    if (list->words == NULL) {
        return 0;
    }
    list->size = 0;
    list->capacity = INITIAL_CAPACITY;
    return 1;
}

void freeWordList(WordList *list) {
    if (list != NULL && list->words != NULL) {
        free(list->words);
        list->words = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int resizeWordList(WordList *list) {
    size_t newCapacity = list->capacity * 2;
    WordCount *newWords = realloc(list->words, newCapacity * sizeof(WordCount));
    if (newWords == NULL) {
        return 0;
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
        str[i] = tolower((unsigned char)str[i]);
    }
}

int findWord(WordList *list, const char *word) {
    if (list == NULL || word == NULL) {
        return -1;
    }
    for (size_t i = 0; i < list->size; i++) {
        if (strcmp(list->words[i].word, word) == 0) {
            return (int)i;
        }
    }
    return -1;
}

int addWord(WordList *list, const char *word) {
    if (list == NULL || word == NULL || strlen(word) == 0) {
        return 0;
    }

    int index = findWord(list, word);
    if (index >= 0) {
        list->words[index].count++;
        return 1;
    }

    if (list->size >= list->capacity) {
        if (!resizeWordList(list)) {
            return 0;
        }
    }

    strncpy(list->words[list->size].word, word, MAX_WORD_LEN - 1);
    list->words[list->size].word[MAX_WORD_LEN - 1] = '\0';
    list->words[list->size].count = 1;
    list->size++;
    return 1;
}

int compareWordCount(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    
    if (wb->count != wa->count) {
        return wb->count - wa->count;
    }
    return strcmp(wa->word, wb->word);
}

int processText(WordList *list, const char *text) {
    if (list == NULL || text == NULL) {
        return 0;
    }

    char buffer[MAX_WORD_LEN];
    size_t bufIndex = 0;
    
    for (size_t i = 0; text[i] != '\0'; i++) {
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
                    return 0;
                }
                bufIndex = 0;
            }
        }
    }
    
    if (bufIndex > 0) {
        buffer[bufIndex] = '\0';
        toLowerCase(buffer);
        if (!addWord(list, buffer)) {
            return 0;
        }
    }
    
    return 1;
}

void findMostCommonWords(const char *text, int n) {
    if (text == NULL || n <= 0) {
        fprintf(stderr, "Invalid input parameters\n");
        return;
    }

    WordList list;
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

    size_t displayCount = (size_t)n < list.size ? (size_t)n : list.size;
    
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
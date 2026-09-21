#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <errno.h>
#include <limits.h>

#define MAX_WORD_LEN 100
#define INITIAL_CAPACITY 1000

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int32_t count;
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
    
    if (INITIAL_CAPACITY == 0 || INITIAL_CAPACITY > SIZE_MAX / sizeof(WordCount)) {
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
        free(list->words);
        list->words = NULL;
        list->size = 0;
        list->capacity = 0;
    }
}

int resizeWordList(WordList *list) {
    if (list == NULL || list->words == NULL) {
        return 0;
    }
    
    if (list->capacity == 0) {
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
    
    size_t oldCapacity = list->capacity;
    list->words = newWords;
    list->capacity = newCapacity;
    
    memset(list->words + oldCapacity, 0, (newCapacity - oldCapacity) * sizeof(WordCount));
    
    return 1;
}

void toLowerCase(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }
    for (size_t i = 0; i < len && str[i] != '\0'; i++) {
        str[i] = (char)tolower((unsigned char)str[i]);
    }
}

int findWord(WordList *list, const char *word) {
    if (list == NULL || word == NULL || list->words == NULL) {
        return -1;
    }
    
    size_t wordLen = strnlen(word, MAX_WORD_LEN);
    if (wordLen == 0 || wordLen >= MAX_WORD_LEN) {
        return -1;
    }
    
    for (size_t i = 0; i < list->size; i++) {
        if (strncmp(list->words[i].word, word, MAX_WORD_LEN) == 0) {
            if (i > INT32_MAX) {
                return -1;
            }
            return (int)i;
        }
    }
    return -1;
}

int addWord(WordList *list, const char *word) {
    if (list == NULL || word == NULL) {
        return 0;
    }
    
    size_t wordLen = strnlen(word, MAX_WORD_LEN);
    if (wordLen == 0 || wordLen >= MAX_WORD_LEN) {
        return 0;
    }

    int index = findWord(list, word);
    if (index >= 0) {
        if (list->words[index].count < INT32_MAX) {
            list->words[index].count++;
        }
        return 1;
    }

    if (list->size >= list->capacity) {
        if (!resizeWordList(list)) {
            return 0;
        }
    }

    if (list->size < list->capacity) {
        size_t copyLen = wordLen < MAX_WORD_LEN - 1 ? wordLen : MAX_WORD_LEN - 1;
        if (copyLen >= MAX_WORD_LEN) {
            return 0;
        }
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(list->words[list->size].word, word, MAX_WORD_LEN - 1);
        list->words[list->size].word[MAX_WORD_LEN - 1] = '\0';
        list->words[list->size].count = 1;
        list->size++;
        return 1;
    }
    
    return 0;
}

int compareWordCount(const void *a, const void *b) {
    if (a == NULL || b == NULL) {
        return 0;
    }
    
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    
    if (wb->count > wa->count) {
        return 1;
    } else if (wb->count < wa->count) {
        return -1;
    }
    return strncmp(wa->word, wb->word, MAX_WORD_LEN);
}

int processText(WordList *list, const char *text) {
    if (list == NULL || text == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN];
    size_t bufIndex = 0;
    size_t textLen = strnlen(text, SIZE_MAX);
    
    if (textLen == 0) {
        return 1;
    }
    
    for (size_t i = 0; i < textLen && text[i] != '\0'; i++) {
        unsigned char c = (unsigned char)text[i];
        
        if (isalnum(c) || c == '\'') {
            if (bufIndex < MAX_WORD_LEN - 1) {
                buffer[bufIndex++] = (char)c;
            }
        } else {
            if (bufIndex > 0) {
                if (bufIndex >= MAX_WORD_LEN) {
                    bufIndex = MAX_WORD_LEN - 1;
                }
                buffer[bufIndex] = '\0';
                toLowerCase(buffer, bufIndex);
                if (!addWord(list, buffer)) {
                    return 0;
                }
                bufIndex = 0;
            }
        }
    }
    
    if (bufIndex > 0) {
        if (bufIndex >= MAX_WORD_LEN) {
            bufIndex = MAX_WORD_LEN - 1;
        }
        buffer[bufIndex] = '\0';
        toLowerCase(buffer, bufIndex);
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
    for (size_t i = 0; i < displayCount && i < list.size; i++) {
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
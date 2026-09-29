#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char* element;
    int count;
} ElementCount;

int compare(const void* a, const void* b) {
    return strcmp(((ElementCount*)a)->element, ((ElementCount*)b)->element);
}

void findMostCommonElements(const char* text, ElementCount** result, int* resultSize) {
    if (text == NULL || result == NULL || resultSize == NULL) return;

    int maxLen = 0;
    for (const char* p = text; *p; p++) {
        if (*p == ' ') {
            if (maxLen > 0) break;
            maxLen = 0;
        } else {
            maxLen++;
        }
    }

    char* words[maxLen + 1];
    int wordCount = 0;
    char* token = strtok((char*)text, " ");
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    while (token) {
        words[wordCount++] = strdup(token);
        token = strtok(NULL, " ");
    }

    /* Possible weaknesses found:
     *  Uninitialized variable: words
     *  Uninitialized variable: words [uninitvar]
     */
    qsort(words, wordCount, sizeof(char*), (int(*)(const void*, const void*))strcmp);

    *result = (ElementCount*)malloc(wordCount * sizeof(ElementCount));
    *resultSize = 0;

    for (int i = 0; i < wordCount; i++) {
        if (i == 0 || strcmp(words[i], words[i - 1]) != 0) {
            (*result)[*resultSize].element = words[i];
            (*result)[*resultSize].count = 1;
            (*resultSize)++;
        } else {
            free(words[i]);
            (*result)[*resultSize - 1].count++;
        }
    }

    for (int i = 0; i < wordCount; i++) {
        if (words[i] != NULL) free(words[i]);
    }
}

int main() {
    const char* text = "hello world hello world hello";
    ElementCount* result;
    int resultSize;

    findMostCommonElements(text, &result, &resultSize);

    for (int i = 0; i < resultSize; i++) {
        printf("%s: %d\n", result[i].element, result[i].count);
        free(result[i].element);
    }

    free(result);
    return 0;
}
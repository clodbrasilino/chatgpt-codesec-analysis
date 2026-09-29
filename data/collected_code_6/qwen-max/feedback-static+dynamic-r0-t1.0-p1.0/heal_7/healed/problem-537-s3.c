#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

char* findFirstRepeatedWord(const char* input) {
    char* words[MAX_WORDS] = {NULL};
    int word_count = 0;
    const char* p = input;
    const char* start = p;

    while (*p) {
        if (*p == ' ' || *p == '\n' || *p == '\t') {
            if (start != p) {
                size_t len = p - start;
                for (int i = 0; i < word_count; ++i) {
                    if (len < MAX_WORD_LENGTH && strncmp(words[i], start, len) == 0 && words[i][len] == '\0') {
                        return strdup(start);
                    }
                }
                if (word_count < MAX_WORDS) {
                    words[word_count] = malloc((len + 1) * sizeof(char));
                    if (words[word_count]) {
                        memcpy(words[word_count], start, len);
                        words[word_count][len] = '\0';
                        word_count++;
                    }
                }
            }
            start = p + 1;
        }
        p++;
    }

    if (start != p) {
        size_t len = p - start;
        for (int i = 0; i < word_count; ++i) {
            if (len < MAX_WORD_LENGTH && strncmp(words[i], start, len) == 0 && words[i][len] == '\0') {
                return strdup(start);
            }
        }
    }

    for (int i = 0; i < word_count; ++i) {
        free(words[i]);
    }

    return NULL;
}

int main() {
    const char* input = "This is a test test string to find the first repeated word";
    char* result = findFirstRepeatedWord(input);

    if (result) {
        printf("First repeated word: %s\n", result);
        free(result);
    } else {
        printf("No repeated words found.\n");
    }

    return 0;
}
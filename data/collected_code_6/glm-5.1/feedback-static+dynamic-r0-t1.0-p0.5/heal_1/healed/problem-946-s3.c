#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordCount;

char *str_dup(const char *s) {
    size_t len = strnlen(s, 256);
    char *d = malloc(len + 1);
    if (d) {
        memcpy(d, s, len + 1);
    }
    return d;
}

void find_most_common(const char *text) {
    if (text == NULL) {
        return;
    }

    WordCount *words = NULL;
    size_t capacity = 0;
    size_t size = 0;

    const char *p = text;
    char *buffer = malloc(256);
    if (!buffer) return;

    while (*p) {
        while (*p && !isalpha((unsigned char)*p)) {
            p++;
        }
        if (!*p) {
            break;
        }

        size_t i = 0;
        while (*p && isalpha((unsigned char)*p) && i < 255) {
            buffer[i++] = tolower((unsigned char)*p);
            p++;
        }
        buffer[i] = '\0';

        size_t j;
        int found = 0;
        for (j = 0; j < size; j++) {
            if (strcmp(words[j].word, buffer) == 0) {
                words[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (size >= capacity) {
                size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
                WordCount *new_words = realloc(words, new_capacity * sizeof(WordCount));
                if (!new_words) {
                    for (size_t k = 0; k < size; k++) {
                        free(words[k].word);
                    }
                    free(words);
                    free(buffer);
                    return;
                }
                words = new_words;
                capacity = new_capacity;
            }
            words[size].word = str_dup(buffer);
            if (!words[size].word) {
                for (size_t k = 0; k < size; k++) {
                    free(words[k].word);
                }
                free(words);
                free(buffer);
                return;
            }
            words[size].count = 1;
            size++;
        }
    }

    free(buffer);

    if (size == 0) {
        return;
    }

    int max_count = 0;
    for (size_t i = 0; i < size; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
        }
    }

    printf("Most common elements (count: %d):\n", max_count);
    for (size_t i = 0; i < size; i++) {
        if (words[i].count == max_count) {
            printf("%s\n", words[i].word);
        }
    }

    for (size_t i = 0; i < size; i++) {
        free(words[i].word);
    }
    free(words);
}

int main(void) {
    const char *text = "Hello world! Hello C developers. C is a great language, hello!";
    find_most_common(text);
    return 0;
}
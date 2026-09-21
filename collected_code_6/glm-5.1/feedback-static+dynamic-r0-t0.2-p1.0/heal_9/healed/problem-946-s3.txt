#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordCount;

char *str_dup(const char *s) {
    if (s == NULL) {
        return NULL;
    }
    size_t len = strnlen(s, SIZE_MAX);
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
    size_t buffer_size = 256;
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        return;
    }

    while (*p) {
        while (*p && !isalpha((unsigned char)*p)) {
            p++;
        }
        if (!*p) {
            break;
        }

        size_t i = 0;
        while (*p && isalpha((unsigned char)*p)) {
            if (i >= buffer_size - 1) {
                size_t new_buffer_size = buffer_size * 2;
                if (new_buffer_size <= buffer_size) {
                    new_buffer_size = buffer_size + 1;
                }
                char *new_buffer = realloc(buffer, new_buffer_size);
                if (!new_buffer) {
                    free(buffer);
                    for (size_t j = 0; j < size; j++) {
                        free(words[j].word);
                    }
                    free(words);
                    return;
                }
                buffer = new_buffer;
                buffer_size = new_buffer_size;
            }
            buffer[i++] = tolower((unsigned char)*p);
            p++;
        }
        buffer[i] = '\0';

        int found = 0;
        for (size_t j = 0; j < size; j++) {
            if (strcmp(words[j].word, buffer) == 0) {
                words[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (size >= capacity) {
                size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
                if (new_capacity <= capacity) {
                    new_capacity = capacity + 1;
                }
                WordCount *new_words = realloc(words, new_capacity * sizeof(WordCount));
                if (!new_words) {
                    free(buffer);
                    for (size_t j = 0; j < size; j++) {
                        free(words[j].word);
                    }
                    free(words);
                    return;
                }
                words = new_words;
                capacity = new_capacity;
            }
            words[size].word = str_dup(buffer);
            if (!words[size].word) {
                free(buffer);
                for (size_t j = 0; j < size; j++) {
                    free(words[j].word);
                }
                free(words);
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
    for (size_t j = 0; j < size; j++) {
        if (words[j].count > max_count) {
            max_count = words[j].count;
        }
    }

    printf("Most common elements (count: %d):\n", max_count);
    for (size_t j = 0; j < size; j++) {
        if (words[j].count == max_count) {
            printf("%s\n", words[j].word);
        }
    }

    for (size_t j = 0; j < size; j++) {
        free(words[j].word);
    }
    free(words);
}

int main(void) {
    const char *text = "Hello world! This is a test. Hello, this test is only a test.";
    find_most_common(text);
    return 0;
}
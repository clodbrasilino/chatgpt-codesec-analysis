#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordCount;

char *str_dup(const char *str) {
    size_t len = strlen(str);
    char *copy = malloc(len + 1);
    if (copy) {
        memcpy(copy, str, len + 1);
    }
    return copy;
}

void add_word(WordCount **words, size_t *unique_count, size_t *capacity, const char *buffer) {
    for (size_t j = 0; j < *unique_count; j++) {
        if (strcmp((*words)[j].word, buffer) == 0) {
            (*words)[j].count++;
            return;
        }
    }
    
    if (*unique_count >= *capacity) {
        size_t new_capacity = *capacity == 0 ? 16 : *capacity * 2;
        WordCount *new_words = realloc(*words, new_capacity * sizeof(WordCount));
        if (new_words == NULL) {
            for (size_t k = 0; k < *unique_count; k++) {
                free((*words)[k].word);
            }
            free(*words);
            exit(EXIT_FAILURE);
        }
        *words = new_words;
        *capacity = new_capacity;
    }
    
    (*words)[*unique_count].word = str_dup(buffer);
    if ((*words)[*unique_count].word == NULL) {
        for (size_t k = 0; k < *unique_count; k++) {
            free((*words)[k].word);
        }
        free(*words);
        exit(EXIT_FAILURE);
    }
    (*words)[*unique_count].count = 1;
    (*unique_count)++;
}

void find_most_common(const char *text) {
    if (text == NULL) {
        return;
    }

    WordCount *words = NULL;
    size_t unique_count = 0;
    size_t capacity = 0;
    size_t buf_size = 256;
    char *buffer = malloc(buf_size);
    if (buffer == NULL) {
        return;
    }
    size_t buf_idx = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            if (buf_idx >= buf_size - 1) {
                buf_size *= 2;
                char *new_buffer = realloc(buffer, buf_size);
                if (new_buffer == NULL) {
                    free(buffer);
                    for (size_t k = 0; k < unique_count; k++) {
                        free(words[k].word);
                    }
                    free(words);
                    return;
                }
                buffer = new_buffer;
            }
            buffer[buf_idx++] = tolower((unsigned char)text[i]);
        } else {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                add_word(&words, &unique_count, &capacity, buffer);
                buf_idx = 0;
            }
        }
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        add_word(&words, &unique_count, &capacity, buffer);
    }

    free(buffer);

    if (unique_count == 0) {
        return;
    }

    int max_count = 0;
    for (size_t i = 0; i < unique_count; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
        }
    }

    printf("Most common elements (count: %d):\n", max_count);
    for (size_t i = 0; i < unique_count; i++) {
        if (words[i].count == max_count) {
            printf("%s\n", words[i].word);
        }
    }

    for (size_t i = 0; i < unique_count; i++) {
        free(words[i].word);
    }
    free(words);
}

int main(void) {
    const char *text = "Hello world! Hello C developers. C is great, C is fast.";
    find_most_common(text);
    return 0;
}
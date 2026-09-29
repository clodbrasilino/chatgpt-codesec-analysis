#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    int count;
} WordCount;

char *str_dup(const char *str, size_t max_len) {
    const char *end = memchr(str, '\0', max_len);
    size_t len = end ? (size_t)(end - str) : max_len;
    char *copy = malloc(len + 1);
    if (copy) {
        if (len > 0) {
            memcpy(copy, str, len);
        }
        copy[len] = '\0';
    }
    return copy;
}

void find_most_common(const char *text) {
    if (text == NULL) {
        return;
    }

    WordCount *words = NULL;
    size_t unique_count = 0;
    size_t capacity = 0;
    char *buffer = calloc(256, sizeof(char));
    if (buffer == NULL) {
        return;
    }
    size_t max_buf = 256;
    size_t buf_idx = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            if (buf_idx >= max_buf - 1) {
                size_t new_max_buf = max_buf * 2;
                char *new_buffer = realloc(buffer, new_max_buf);
                if (new_buffer == NULL) {
                    for (size_t k = 0; k < unique_count; k++) free(words[k].word);
                    free(words);
                    free(buffer);
                    return;
                }
                buffer = new_buffer;
                max_buf = new_max_buf;
            }
            buffer[buf_idx++] = tolower((unsigned char)text[i]);
        } else {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                buf_idx = 0;

                int found = 0;
                for (size_t j = 0; j < unique_count; j++) {
                    if (strcmp(words[j].word, buffer) == 0) {
                        words[j].count++;
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    if (unique_count >= capacity) {
                        size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
                        WordCount *new_words = realloc(words, new_capacity * sizeof(WordCount));
                        if (new_words == NULL) {
                            for (size_t k = 0; k < unique_count; k++) free(words[k].word);
                            free(words);
                            free(buffer);
                            return;
                        }
                        words = new_words;
                        capacity = new_capacity;
                    }

                    words[unique_count].word = str_dup(buffer, max_buf);
                    if (words[unique_count].word == NULL) {
                        for (size_t k = 0; k < unique_count; k++) free(words[k].word);
                        free(words);
                        free(buffer);
                        return;
                    }
                    words[unique_count].count = 1;
                    unique_count++;
                }
            }
        }
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';

        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (strcmp(words[j].word, buffer) == 0) {
                words[j].count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (unique_count >= capacity) {
                size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
                WordCount *new_words = realloc(words, new_capacity * sizeof(WordCount));
                if (new_words == NULL) {
                    for (size_t k = 0; k < unique_count; k++) free(words[k].word);
                    free(words);
                    free(buffer);
                    return;
                }
                words = new_words;
                capacity = new_capacity;
            }

            words[unique_count].word = str_dup(buffer, max_buf);
            if (words[unique_count].word == NULL) {
                for (size_t k = 0; k < unique_count; k++) free(words[k].word);
                free(words);
                free(buffer);
                return;
            }
            words[unique_count].count = 1;
            unique_count++;
        }
    }

    int max_count = 0;
    for (size_t i = 0; i < unique_count; i++) {
        if (words[i].count > max_count) {
            max_count = words[i].count;
        }
    }

    if (max_count > 0) {
        printf("Most common elements (count: %d):\n", max_count);
        for (size_t i = 0; i < unique_count; i++) {
            if (words[i].count == max_count) {
                printf("%s\n", words[i].word);
            }
        }
    }

    for (size_t i = 0; i < unique_count; i++) {
        free(words[i].word);
    }
    free(words);
    free(buffer);
}

int main(void) {
    const char *sample_text = "Hello world! This is a test. Hello again, this test is only a test.";
    find_most_common(sample_text);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **shortlist_words(const char **words, size_t num_words, size_t n, size_t *out_count);
void free_shortlist(char **list, size_t count);

char **shortlist_words(const char **words, size_t num_words, size_t n, size_t *out_count) {
    if (!words || !out_count) {
        if (out_count) {
            *out_count = 0;
        }
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < num_words; i++) {
        if (words[i] && strlen(words[i]) > n) {
            count++;
        }
    }

    *out_count = count;
    if (count == 0) {
        return NULL;
    }

    char **result = malloc(count * sizeof(char *));
    if (!result) {
        *out_count = 0;
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < num_words; i++) {
        if (words[i]) {
            size_t len = strlen(words[i]);
            if (len > n) {
                result[index] = malloc(len + 1);
                if (!result[index]) {
                    for (size_t j = 0; j < index; j++) {
                        free(result[j]);
                    }
                    free(result);
                    *out_count = 0;
                    return NULL;
                }
                memcpy(result[index], words[i], len + 1);
                index++;
            }
        }
    }

    return result;
}

void free_shortlist(char **list, size_t count) {
    if (!list) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(list[i]);
    }
    free(list);
}

int main(void) {
    const char *word_list[] = {
        "apple",
        "cat",
        "banana",
        "dog",
        "elephant",
        "fox"
    };
    
    size_t num_words = sizeof(word_list) / sizeof(word_list[0]);
    size_t threshold = 4;
    size_t out_count = 0;

    char **shortlisted = shortlist_words(word_list, num_words, threshold, &out_count);

    if (shortlisted) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%s\n", shortlisted[i]);
        }
        free_shortlist(shortlisted, out_count);
    }

    return 0;
}
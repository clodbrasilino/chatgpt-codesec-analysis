#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORDS 100
#define MAX_SENTENCE_LEN 8192

typedef struct {
    char *word;
    int position;
} AdverbMatch;

size_t get_safe_len(const char *str, size_t max_len) {
    size_t len = 0;
    while (str && str[len] != '\0' && len < max_len) {
        len++;
    }
    return len;
}

bool ends_with_ly(const char *word) {
    if (!word) return false;
    size_t len = get_safe_len(word, MAX_SENTENCE_LEN);
    if (len < 3) return false;
    return (tolower((unsigned char)word[len - 2]) == 'l' && tolower((unsigned char)word[len - 1]) == 'y');
}

void find_adverbs(const char *sentence, AdverbMatch **matches, int *match_count) {
    if (!sentence || !matches || !match_count) return;

    size_t sentence_len = get_safe_len(sentence, MAX_SENTENCE_LEN);
    if (sentence_len == 0 || sentence_len >= MAX_SENTENCE_LEN) return;

    *match_count = 0;
    *matches = (AdverbMatch *)malloc(MAX_WORDS * sizeof(AdverbMatch));
    if (*matches == NULL) {
        return;
    }

    char *sentence_copy = (char *)malloc(sentence_len + 1);
    if (!sentence_copy) {
        free(*matches);
        *matches = NULL;
        return;
    }
    
    snprintf(sentence_copy, sentence_len + 1, "%s", sentence);

    const char *delimiters = " \t\n\r\f\v.,;:!?\"()";
    char *saveptr = NULL;
    char *token = strtok_r(sentence_copy, delimiters, &saveptr);
    int current_pos = 0;

    const char *original_ptr = sentence;

    while (token != NULL) {
        char *found = strstr(original_ptr, token);
        if (found) {
            current_pos = (int)(found - sentence);
            original_ptr = found + get_safe_len(token, MAX_SENTENCE_LEN);
        }

        if (ends_with_ly(token) && *match_count < MAX_WORDS) {
            size_t token_len = get_safe_len(token, MAX_SENTENCE_LEN);
            (*matches)[*match_count].word = (char *)malloc(token_len + 1);
            if ((*matches)[*match_count].word != NULL) {
                snprintf((*matches)[*match_count].word, token_len + 1, "%s", token);
                (*matches)[*match_count].position = current_pos;
                (*match_count)++;
            }
        }
        token = strtok_r(NULL, delimiters, &saveptr);
    }

    free(sentence_copy);
}

int main(void) {
    const char *sentence = "He quickly ran quietly to the store, carefully avoiding the dog.";
    AdverbMatch *matches = NULL;
    int match_count = 0;

    find_adverbs(sentence, &matches, &match_count);

    if (matches != NULL) {
        printf("Sentence: \"%s\"\n", sentence);
        for (int i = 0; i < match_count; i++) {
            printf("Adverb: '%s', Position: %d\n", matches[i].word, matches[i].position);
            free(matches[i].word);
        }
        free(matches);
    } else {
        printf("Memory allocation failed or invalid input.\n");
    }

    return 0;
}
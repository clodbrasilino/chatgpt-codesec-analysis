#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORDS 100

typedef struct {
    char *word;
    int position;
} AdverbMatch;

bool ends_with_ly(const char *word) {
    if (!word) {
        return false;
    }
    size_t len = strnlen(word, 4096);
    if (len < 3) {
        return false;
    }
    return (tolower((unsigned char)word[len - 2]) == 'l' && 
            tolower((unsigned char)word[len - 1]) == 'y');
}

void find_adverbs(const char *sentence, AdverbMatch **matches, int *match_count) {
    if (!sentence || !matches || !match_count) {
        return;
    }

    *matches = malloc(MAX_WORDS * sizeof(AdverbMatch));
    if (!*matches) {
        *match_count = -1;
        return;
    }

    *match_count = 0;
    
    char *sentence_copy = strdup(sentence);
    if (!sentence_copy) {
        free(*matches);
        *matches = NULL;
        *match_count = -1;
        return;
    }

    char *token;
    char *saveptr;
    const char *delimiters = " \t\n\r.,!?;:\"()[]{}";
    int current_pos = 0;

    token = strtok_r(sentence_copy, delimiters, &saveptr);
    while (token != NULL) {
        if (ends_with_ly(token)) {
            if (*match_count < MAX_WORDS) {
                char *word_copy = strdup(token);
                if (word_copy) {
                    (*matches)[*match_count].word = word_copy;
                    
                    const char *pos_ptr = strstr(sentence + current_pos, token);
                    if (pos_ptr) {
                        (*matches)[*match_count].position = pos_ptr - sentence;
                        current_pos = (pos_ptr - sentence) + strnlen(token, 4096);
                    } else {
                        (*matches)[*match_count].position = -1;
                    }
                    
                    (*match_count)++;
                }
            }
        }
        token = strtok_r(NULL, delimiters, &saveptr);
    }

    free(sentence_copy);
}

int main(void) {
    const char *sentence = "The quick brown fox quickly jumped over the lazy dog, acting very foolishly.";
    AdverbMatch *adverbs = NULL;
    int count = 0;

    find_adverbs(sentence, &adverbs, &count);

    if (count < 0) {
        fprintf(stderr, "Error allocating memory.\n");
        return EXIT_FAILURE;
    }

    printf("Sentence: %s\n", sentence);
    for (int i = 0; i < count; i++) {
        printf("Adverb: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
        free(adverbs[i].word);
    }

    if (adverbs != NULL) {
        free(adverbs);
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_WORD_LENGTH 50
#define MAX_WORDS 100

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LENGTH];
    int position;
} AdverbMatch;

bool ends_with_ly(const char *word) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
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
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy((*matches)[*match_count].word, token, MAX_WORD_LENGTH - 1);
                (*matches)[*match_count].word[MAX_WORD_LENGTH - 1] = '\0';
                
                const char *pos_ptr = strstr(sentence + current_pos, token);
                if (pos_ptr) {
                    (*matches)[*match_count].position = pos_ptr - sentence;
                    /* Possible weaknesses found:
                     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                     */
                    current_pos = (pos_ptr - sentence) + strlen(token);
                } else {
                    (*matches)[*match_count].position = -1;
                }
                
                (*match_count)++;
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
    }

    if (adverbs != NULL) {
        free(adverbs);
    }

    return EXIT_SUCCESS;
}
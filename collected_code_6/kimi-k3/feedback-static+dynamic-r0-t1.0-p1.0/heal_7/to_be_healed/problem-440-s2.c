#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_WORD_LENGTH 256
#define MAX_ADVERBS 100
#define MAX_SENTENCE_LENGTH 1024

typedef struct {
    char *word;
    size_t position;
} Adverb;

static bool ends_with_ly(const char *word, size_t len) {
    if (len < 3) {
        return false;
    }
    return (word[len - 2] == 'l' && word[len - 1] == 'y');
}

static bool is_word_char(int c) {
    return isalnum(c) || c == '\'' || c == '-';
}

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

static void free_adverbs(Adverb *adverbs, size_t count) {
    if (adverbs == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(adverbs[i].word);
    }
    free(adverbs);
}

static size_t find_adverbs(const char *sentence, size_t sentence_len, Adverb *adverbs, size_t max_adverbs) {
    size_t adverb_count = 0;
    size_t i = 0;
    
    if (sentence == NULL || adverbs == NULL || max_adverbs == 0) {
        return 0;
    }
    
    while (i < sentence_len && adverb_count < max_adverbs) {
        if (is_word_char((unsigned char)sentence[i])) {
            size_t word_start = i;
            size_t word_len = 0;
            
            while (i < sentence_len && is_word_char((unsigned char)sentence[i])) {
                i++;
                word_len++;
            }
            
            if (word_len > 0 && word_len < MAX_WORD_LENGTH && ends_with_ly(sentence + word_start, word_len)) {
                char *word_copy = malloc(word_len + 1);
                if (word_copy == NULL) {
                    break;
                }
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(word_copy, sentence + word_start, word_len);
                word_copy[word_len] = '\0';
                
                adverbs[adverb_count].word = word_copy;
                adverbs[adverb_count].position = word_start;
                adverb_count++;
            }
        } else {
            i++;
        }
    }
    
    return adverb_count;
}

int main(void) {
    char *sentence = NULL;
    Adverb *adverbs = NULL;
    size_t adverb_count = 0;
    size_t sentence_len;
    size_t buffer_size = MAX_SENTENCE_LENGTH;
    
    sentence = malloc(buffer_size);
    if (sentence == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter a sentence: ");
    
    if (fgets(sentence, buffer_size, stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        free(sentence);
        return EXIT_FAILURE;
    }
    
    sentence_len = safe_strlen(sentence, buffer_size);
    
    if (sentence_len > 0 && sentence[sentence_len - 1] == '\n') {
        sentence[sentence_len - 1] = '\0';
        sentence_len--;
    }
    
    adverbs = calloc(MAX_ADVERBS, sizeof(Adverb));
    if (adverbs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(sentence);
        return EXIT_FAILURE;
    }
    
    adverb_count = find_adverbs(sentence, sentence_len, adverbs, MAX_ADVERBS);
    
    if (adverb_count == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Found %zu adverb(s):\n", adverb_count);
        for (size_t i = 0; i < adverb_count; i++) {
            printf("  \"%s\" at position %zu\n", adverbs[i].word, adverbs[i].position);
        }
    }
    
    free_adverbs(adverbs, adverb_count);
    free(sentence);
    
    return EXIT_SUCCESS;
}
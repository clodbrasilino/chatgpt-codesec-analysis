#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_ADVERBS 100
#define MAX_WORD_LEN 100
#define MAX_SENTENCE_LEN 10000

typedef struct {
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

int is_adverb(const char *word) {
    if (word == NULL) return 0;
    
    size_t len = strlen(word);
    if (len < 3) return 0;
    
    if (len >= MAX_WORD_LEN) return 0;
    
    if (word[len - 2] == 'l' && word[len - 1] == 'y') return 1;
    return 0;
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return -1;
    }

    int count = 0;
    size_t sentence_len = strlen(sentence);
    
    if (sentence_len == 0 || sentence_len >= MAX_SENTENCE_LEN) return -1;
    
    char *buffer = (char *)malloc(sentence_len + 1);
    if (buffer == NULL) {
        return -1;
    }
    
    strcpy(buffer, sentence);

    char *saveptr;
    char *token = strtok_r(buffer, " ,.!?;:\"()[]{}", &saveptr);
    int position = 0;

    while (token != NULL && count < max_adverbs) {
        if (is_adverb(token)) {
            size_t token_len = strlen(token);
            if (token_len >= MAX_WORD_LEN) {
                token_len = MAX_WORD_LEN - 1;
            }
            memcpy(adverbs[count].word, token, token_len);
            adverbs[count].word[token_len] = '\0';
            adverbs[count].position = position;
            count++;
        }
        position++;
        token = strtok_r(NULL, " ,.!?;:\"()[]{}", &saveptr);
    }

    free(buffer);
    return count;
}

int main(void) {
    char sentence[MAX_SENTENCE_LEN];
    AdverbInfo adverbs[MAX_ADVERBS];

    printf("Enter a sentence: ");
    if (fgets(sentence, sizeof(sentence), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    size_t len = strlen(sentence);
    if (len > 0 && sentence[len - 1] == '\n') {
        sentence[len - 1] = '\0';
        len--;
    }

    if (len >= sizeof(sentence) - 1) {
        fprintf(stderr, "Input sentence too long\n");
        return 1;
    }

    int num_adverbs = find_adverbs(sentence, adverbs, MAX_ADVERBS);

    if (num_adverbs < 0) {
        fprintf(stderr, "Error processing sentence\n");
        return 1;
    }

    if (num_adverbs == 0) {
        printf("No adverbs found.\n");
    } else {
        printf("Adverbs found:\n");
        for (int i = 0; i < num_adverbs; i++) {
            printf("Word: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
        }
    }

    return 0;
}
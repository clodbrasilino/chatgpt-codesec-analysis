#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

typedef struct {
    char word[MAX_WORD_LEN];
    int position;
} AdverbInfo;

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str != NULL) {
        while (len < max_len && str[len] != '\0') {
            len++;
        }
    }
    return len;
}

static int safe_tolower(int c) {
    return tolower((unsigned char)c);
}

int is_adverb(const char *word) {
    size_t len;
    if (word == NULL) {
        return 0;
    }
    len = safe_strlen(word, MAX_WORD_LEN);
    if (len < 3 || len >= MAX_WORD_LEN) {
        return 0;
    }
    return (word[len - 2] == 'l' && word[len - 1] == 'y');
}

int find_adverbs(const char *sentence, AdverbInfo *adverbs, int max_adverbs) {
    size_t sentence_len;
    char *copy;
    int count;
    int position;
    char *saveptr;
    char *token;

    if (sentence == NULL || adverbs == NULL || max_adverbs <= 0) {
        return -1;
    }

    sentence_len = safe_strlen(sentence, (size_t)-1);
    if (sentence_len == 0) {
        return 0;
    }

    copy = malloc(sentence_len + 1);
    if (copy == NULL) {
        return -1;
    }

    if (sentence_len + 1 <= sentence_len) {
        free(copy);
        return -1;
    }

    memcpy(copy, sentence, sentence_len);
    copy[sentence_len] = '\0';

    count = 0;
    position = 0;
    token = strtok_r(copy, " \t\n\r.,;:!?\"'()[]{}", &saveptr);

    while (token != NULL && count < max_adverbs) {
        size_t len = safe_strlen(token, MAX_WORD_LEN);

        if (len > 0 && len < MAX_WORD_LEN) {
            char lower[MAX_WORD_LEN];
            size_t j;
            size_t copy_len = len;

            for (j = 0; j < copy_len && j < MAX_WORD_LEN - 1; j++) {
                lower[j] = (char)safe_tolower((unsigned char)token[j]);
            }
            lower[j] = '\0';

            if (is_adverb(lower)) {
                size_t k;
                size_t word_copy_len = copy_len;

                if (word_copy_len >= MAX_WORD_LEN) {
                    word_copy_len = MAX_WORD_LEN - 1;
                }

                for (k = 0; k < word_copy_len; k++) {
                    adverbs[count].word[k] = token[k];
                }
                adverbs[count].word[word_copy_len] = '\0';
                adverbs[count].position = position;
                count++;
            }
        }
        position++;
        token = strtok_r(NULL, " \t\n\r.,;:!?\"'()[]{}", &saveptr);
    }

    free(copy);
    return count;
}

int main(void) {
    const char *sentence = "The quick brown fox jumps quickly and silently over the lazy dog.";
    AdverbInfo adverbs[MAX_WORDS];
    int num_adverbs;
    int i;

    num_adverbs = find_adverbs(sentence, adverbs, MAX_WORDS);

    if (num_adverbs < 0) {
        fprintf(stderr, "Error processing sentence\n");
        return EXIT_FAILURE;
    }

    printf("Sentence: %s\n", sentence);
    printf("Found %d adverb(s):\n", num_adverbs);

    for (i = 0; i < num_adverbs; i++) {
        printf("  Word: %s, Position: %d\n", adverbs[i].word, adverbs[i].position);
    }

    return EXIT_SUCCESS;
}
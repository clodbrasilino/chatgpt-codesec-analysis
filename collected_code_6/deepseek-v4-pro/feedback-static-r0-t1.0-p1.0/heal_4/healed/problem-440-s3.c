#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_WORD_LENGTH 127
#define MAX_CAPACITY 1024

typedef struct {
    char word[MAX_WORD_LENGTH + 1];
    int position;
} AdverbInfo;

static int is_adverb(const char *word, size_t word_len) {
    if (word == NULL || word_len < 2) {
        return 0;
    }
    return word[word_len - 2] == 'l' && word[word_len - 1] == 'y';
}

static int find_all_adverbs(const char *sentence, AdverbInfo **adverbs, int *count) {
    if (sentence == NULL || adverbs == NULL || count == NULL) {
        return -1;
    }

    *adverbs = NULL;
    *count = 0;

    size_t len = strnlen(sentence, INT32_MAX);
    if (len == 0) {
        return 0;
    }

    char *buffer = (char *)malloc(len + 1);
    if (buffer == NULL) {
        return -1;
    }
    memcpy(buffer, sentence, len);
    buffer[len] = '\0';

    int capacity = 0;
    AdverbInfo *result = NULL;

    char *saveptr;
    const char *delimiters = " ,.;:!?\"'()\t\n";
    char *token = strtok_r(buffer, delimiters, &saveptr);
    while (token != NULL) {
        size_t token_len = strnlen(token, MAX_WORD_LENGTH + 1);

        if (token_len > MAX_WORD_LENGTH) {
            free(result);
            free(buffer);
            return -1;
        }

        if (is_adverb(token, token_len)) {
            if (*count >= capacity) {
                int new_capacity = capacity == 0 ? 4 : capacity * 2;
                if (new_capacity > MAX_CAPACITY) {
                    free(result);
                    free(buffer);
                    return -1;
                }
                AdverbInfo *new_result = (AdverbInfo *)realloc(result, (size_t)new_capacity * sizeof(AdverbInfo));
                if (new_result == NULL) {
                    free(result);
                    free(buffer);
                    return -1;
                }
                result = new_result;
                capacity = new_capacity;
            }

            strncpy(result[*count].word, token, MAX_WORD_LENGTH);
            result[*count].word[MAX_WORD_LENGTH] = '\0';

            const char *pos_ptr = sentence + (token - buffer);
            while (pos_ptr > sentence && !isspace((unsigned char)*(pos_ptr - 1)) &&
                   strchr(delimiters, *(pos_ptr - 1)) == NULL) {
                pos_ptr--;
            }
            result[*count].position = (int)(pos_ptr - sentence);

            (*count)++;
        }
        token = strtok_r(NULL, delimiters, &saveptr);
    }

    free(buffer);

    if (*count == 0) {
        free(result);
        *adverbs = NULL;
    } else {
        *adverbs = result;
    }

    return 0;
}

int main(void) {
    const char *sentence = "The cat quickly ran very slowly and happily through the garden.";
    AdverbInfo *adverbs = NULL;
    int count = 0;

    int status = find_all_adverbs(sentence, &adverbs, &count);
    if (status != 0) {
        fprintf(stderr, "Error processing sentence\n");
        return EXIT_FAILURE;
    }

    printf("Adverbs found: %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("Position %d: %s\n", adverbs[i].position, adverbs[i].word);
    }

    free(adverbs);
    return EXIT_SUCCESS;
}
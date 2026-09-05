#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    size_t position;
} Adverb;

Adverb *find_adverbs(const char *sentence, size_t *count) {
    if (sentence == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    size_t capacity = 10;
    Adverb *adverbs = malloc(capacity * sizeof(Adverb));
    if (adverbs == NULL) {
        return NULL;
    }

    const char *ptr = sentence;
    while (*ptr != '\0') {
        while (*ptr != '\0' && isspace((unsigned char)*ptr)) {
            ptr++;
        }

        if (*ptr == '\0') {
            break;
        }

        size_t position = ptr - sentence;
        const char *start = ptr;

        while (*ptr != '\0' && !isspace((unsigned char)*ptr)) {
            ptr++;
        }

        size_t length = ptr - start;

        if (length > 2 && start[length - 2] == 'l' && start[length - 1] == 'y') {
            if (*count >= capacity) {
                capacity *= 2;
                Adverb *temp = realloc(adverbs, capacity * sizeof(Adverb));
                if (temp == NULL) {
                    for (size_t i = 0; i < *count; i++) {
                        free(adverbs[i].word);
                    }
                    free(adverbs);
                    *count = 0;
                    return NULL;
                }
                adverbs = temp;
            }

            adverbs[*count].word = malloc(length + 1);
            if (adverbs[*count].word == NULL) {
                for (size_t i = 0; i < *count; i++) {
                    free(adverbs[i].word);
                }
                free(adverbs);
                *count = 0;
                return NULL;
            }

            memcpy(adverbs[*count].word, start, length);
            adverbs[*count].word[length] = '\0';
            adverbs[*count].position = position;
            (*count)++;
        }
    }

    if (*count == 0) {
        free(adverbs);
        return NULL;
    }

    Adverb *final_adverbs = realloc(adverbs, *count * sizeof(Adverb));
    if (final_adverbs != NULL) {
        adverbs = final_adverbs;
    }

    return adverbs;
}

int main(void) {
    const char *sentence = "He quickly ran to the slowly moving car and happily drove away.";
    size_t count = 0;

    Adverb *adverbs = find_adverbs(sentence, &count);

    if (adverbs != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("Adverb: %s, Position: %zu\n", adverbs[i].word, adverbs[i].position);
            free(adverbs[i].word);
        }
        free(adverbs);
    } else {
        printf("No adverbs found or memory allocation failed.\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    size_t position;
} Adverb;

static int ends_with_ly(const char *word) {
    size_t len = strlen(word);
    if (len < 4) {
        return 0;
    }
    return tolower((unsigned char)word[len - 2]) == 'l' &&
           tolower((unsigned char)word[len - 1]) == 'y';
}

Adverb *find_adverbs(const char *sentence, int *count) {
    if (count != NULL) {
        *count = 0;
    }

    if (sentence == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strlen(sentence);
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        *count = -1;
        return NULL;
    }

    strcpy(copy, sentence);

    Adverb *adverbs = NULL;
    int capacity = 0;
    int n = 0;
    const char *delimiters = " ,.!?;:()[]\"'\n\t";

    char *token = strtok(copy, delimiters);
    while (token != NULL) {
        if (ends_with_ly(token)) {
            if (n == capacity) {
                int new_capacity = capacity == 0 ? 4 : capacity * 2;
                if (new_capacity <= capacity) {
                    free(copy);
                    for (int i = 0; i < n; ++i) {
                        free(adverbs[i].word);
                    }
                    free(adverbs);
                    *count = -1;
                    return NULL;
                }

                Adverb *tmp = realloc(adverbs, (size_t)new_capacity * sizeof(Adverb));
                if (tmp == NULL) {
                    free(copy);
                    for (int i = 0; i < n; ++i) {
                        free(adverbs[i].word);
                    }
                    free(adverbs);
                    *count = -1;
                    return NULL;
                }

                adverbs = tmp;
                capacity = new_capacity;
            }

            size_t word_len = strlen(token);
            adverbs[n].word = malloc(word_len + 1);
            if (adverbs[n].word == NULL) {
                free(copy);
                for (int i = 0; i < n; ++i) {
                    free(adverbs[i].word);
                }
                free(adverbs);
                *count = -1;
                return NULL;
            }

            strcpy(adverbs[n].word, token);
            adverbs[n].position = (size_t)(token - copy);
            ++n;
        }

        token = strtok(NULL, delimiters);
    }

    free(copy);
    *count = n;
    return adverbs;
}

void free_adverbs(Adverb *adverbs, int count) {
    if (adverbs == NULL) {
        return;
    }

    for (int i = 0; i < count; ++i) {
        free(adverbs[i].word);
    }

    free(adverbs);
}

int main(void) {
    const char sentence[] = "He quickly ran slowly and happily.";
    int count = 0;
    Adverb *adverbs = find_adverbs(sentence, &count);

    if (count < 0) {
        fprintf(stderr, "Memory allocation error\n");
        return EXIT_FAILURE;
    }

    if (adverbs == NULL) {
        printf("No adverbs found.\n");
        return EXIT_SUCCESS;
    }

    for (int i = 0; i < count; ++i) {
        printf("%s at %zu\n", adverbs[i].word, adverbs[i].position);
    }

    free_adverbs(adverbs, count);
    return EXIT_SUCCESS;
}
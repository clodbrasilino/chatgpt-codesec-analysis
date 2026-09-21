#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char *word;
    size_t position;
} Adverb;

static int safe_get_length(const char *s, size_t max_len, size_t *out_len) {
    size_t i = 0;
    while (i < max_len && s[i] != '\0') {
        i++;
    }
    if (i == max_len) {
        return -1;
    }
    *out_len = i;
    return 0;
}

static int ends_with_ly_n(const char *word, size_t len) {
    if (len < 4) {
        return 0;
    }
    return tolower((unsigned char)word[len - 2]) == 'l' &&
           tolower((unsigned char)word[len - 1]) == 'y';
}

Adverb *find_adverbs(const char *sentence, int *count) {
    if (count == NULL) {
        return NULL;
    }
    *count = 0;

    if (sentence == NULL) {
        return NULL;
    }

    size_t sentence_len;
    if (safe_get_length(sentence, 1000000, &sentence_len) != 0) {
        *count = -1;
        return NULL;
    }

    size_t copy_size = sentence_len + 1;
    char *copy = malloc(copy_size);
    if (copy == NULL) {
        *count = -1;
        return NULL;
    }
    if (copy_size < sentence_len + 1) {
        free(copy);
        *count = -1;
        return NULL;
    }
    memcpy(copy, sentence, copy_size);

    Adverb *adverbs = NULL;
    int capacity = 0;
    int n = 0;
    const char *delimiters = " ,.!?;:()[]\"'\n\t";

    char *token = strtok(copy, delimiters);
    while (token != NULL) {
        size_t word_len;
        if (safe_get_length(token, 128, &word_len) != 0) {
            token = strtok(NULL, delimiters);
            continue;
        }

        if (!ends_with_ly_n(token, word_len)) {
            token = strtok(NULL, delimiters);
            continue;
        }

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

        size_t word_allocated = word_len + 1;
        adverbs[n].word = malloc(word_allocated);
        if (adverbs[n].word == NULL) {
            free(copy);
            for (int i = 0; i < n; ++i) {
                free(adverbs[i].word);
            }
            free(adverbs);
            *count = -1;
            return NULL;
        }
        if (word_allocated < word_len + 1) {
            free(adverbs[n].word);
            free(copy);
            for (int i = 0; i < n; ++i) {
                free(adverbs[i].word);
            }
            free(adverbs);
            *count = -1;
            return NULL;
        }
        memcpy(adverbs[n].word, token, word_allocated);
        adverbs[n].position = (size_t)(token - copy);
        ++n;

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
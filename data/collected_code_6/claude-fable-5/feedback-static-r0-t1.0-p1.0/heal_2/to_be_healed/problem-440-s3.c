#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 128
#define MAX_SENTENCE_LEN 4096

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    size_t position;
} AdverbMatch;

typedef struct {
    AdverbMatch *matches;
    size_t count;
    size_t capacity;
} AdverbList;

static int adverb_list_init(AdverbList *list)
{
    if (list == NULL) {
        return -1;
    }
    list->capacity = 8;
    list->count = 0;
    list->matches = malloc(list->capacity * sizeof(AdverbMatch));
    if (list->matches == NULL) {
        list->capacity = 0;
        return -1;
    }
    return 0;
}

static int adverb_list_add(AdverbList *list, const char *word, size_t word_len, size_t position)
{
    if (list == NULL || word == NULL || list->matches == NULL) {
        return -1;
    }
    if (word_len >= MAX_WORD_LEN) {
        return -1;
    }
    if (list->count == list->capacity) {
        if (list->capacity > (SIZE_MAX / sizeof(AdverbMatch)) / 2) {
            return -1;
        }
        size_t new_capacity = list->capacity * 2;
        AdverbMatch *tmp = realloc(list->matches, new_capacity * sizeof(AdverbMatch));
        if (tmp == NULL) {
            return -1;
        }
        list->matches = tmp;
        list->capacity = new_capacity;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(list->matches[list->count].word, word, word_len);
    list->matches[list->count].word[word_len] = '\0';
    list->matches[list->count].position = position;
    list->count++;
    return 0;
}

static void adverb_list_free(AdverbList *list)
{
    if (list != NULL) {
        free(list->matches);
        list->matches = NULL;
        list->count = 0;
        list->capacity = 0;
    }
}

static int is_adverb(const char *word, size_t len)
{
    if (word == NULL || len < 3) {
        return 0;
    }
    if (tolower((unsigned char)word[len - 2]) == 'l' &&
        tolower((unsigned char)word[len - 1]) == 'y') {
        return 1;
    }
    return 0;
}

static int find_adverbs(const char *sentence, AdverbList *list)
{
    size_t i = 0;
    size_t len;

    if (sentence == NULL || list == NULL) {
        return -1;
    }

    len = strnlen(sentence, MAX_SENTENCE_LEN);

    while (i < len) {
        if (isalpha((unsigned char)sentence[i])) {
            size_t start = i;
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char buffer[MAX_WORD_LEN];
            size_t word_len = 0;
            int truncated = 0;

            while (i < len && (isalpha((unsigned char)sentence[i]) ||
                               sentence[i] == '\'' || sentence[i] == '-')) {
                if (word_len < MAX_WORD_LEN - 1) {
                    buffer[word_len] = sentence[i];
                    word_len++;
                } else {
                    truncated = 1;
                }
                i++;
            }
            buffer[word_len] = '\0';

            if (!truncated && is_adverb(buffer, word_len)) {
                if (adverb_list_add(list, buffer, word_len, start) != 0) {
                    return -1;
                }
            }
        } else {
            i++;
        }
    }
    return 0;
}

int main(void)
{
    const char *sentence = "She quickly ran home, and he calmly but firmly closed the door.";
    AdverbList list;

    if (adverb_list_init(&list) != 0) {
        fprintf(stderr, "Failed to initialize adverb list\n");
        return EXIT_FAILURE;
    }

    if (find_adverbs(sentence, &list) != 0) {
        fprintf(stderr, "Failed to find adverbs\n");
        adverb_list_free(&list);
        return EXIT_FAILURE;
    }

    printf("Sentence: %s\n", sentence);

    if (list.count == 0) {
        printf("No adverbs found.\n");
    } else {
        for (size_t i = 0; i < list.count; i++) {
            printf("Adverb: %-12s Position: %zu\n",
                   list.matches[i].word, list.matches[i].position);
        }
    }

    adverb_list_free(&list);
    return EXIT_SUCCESS;
}
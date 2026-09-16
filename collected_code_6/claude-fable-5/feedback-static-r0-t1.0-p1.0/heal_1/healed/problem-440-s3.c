#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 128

typedef struct {
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
        return -1;
    }
    return 0;
}

static int adverb_list_add(AdverbList *list, const char *word, size_t position)
{
    if (list == NULL || word == NULL) {
        return -1;
    }
    if (list->count == list->capacity) {
        size_t new_capacity = list->capacity * 2;
        AdverbMatch *tmp = realloc(list->matches, new_capacity * sizeof(AdverbMatch));
        if (tmp == NULL) {
            return -1;
        }
        list->matches = tmp;
        list->capacity = new_capacity;
    }
    if (strlen(word) >= MAX_WORD_LEN) {
        return -1;
    }
    strncpy(list->matches[list->count].word, word, MAX_WORD_LEN - 1);
    list->matches[list->count].word[MAX_WORD_LEN - 1] = '\0';
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

    len = strlen(sentence);

    while (i < len) {
        if (isalpha((unsigned char)sentence[i])) {
            size_t start = i;
            char buffer[MAX_WORD_LEN];
            size_t word_len = 0;

            while (i < len && (isalpha((unsigned char)sentence[i]) ||
                               sentence[i] == '\'' || sentence[i] == '-')) {
                if (word_len < MAX_WORD_LEN - 1) {
                    buffer[word_len] = sentence[i];
                    word_len++;
                }
                i++;
            }
            buffer[word_len] = '\0';

            if (is_adverb(buffer, word_len)) {
                if (adverb_list_add(list, buffer, start) != 0) {
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
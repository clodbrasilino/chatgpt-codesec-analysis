#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

#define MAX_WORD_LEN 256
#define MAX_WORDS 100000

typedef struct {
    char *word;
    int count;
} WordEntry;

static WordEntry *word_entries = NULL;
static int num_entries = 0;
static int max_entries = 0;

int find_or_add_word(const char *word) {
    if (word == NULL) {
        return -1;
    }
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(word_entries[i].word, word) == 0) {
            word_entries[i].count++;
            return i;
        }
    }
    if (num_entries >= max_entries) {
        int new_max = max_entries == 0 ? 1024 : max_entries * 2;
        if (new_max > MAX_WORDS) {
            new_max = MAX_WORDS;
        }
        WordEntry *new_entries = realloc(word_entries, new_max * sizeof(WordEntry));
        if (!new_entries) {
            return -1;
        }
        word_entries = new_entries;
        max_entries = new_max;
    }
    word_entries[num_entries].word = strdup(word);
    if (!word_entries[num_entries].word) {
        return -1;
    }
    word_entries[num_entries].count = 1;
    num_entries++;
    return num_entries - 1;
}

int compare_word_entries(const void *a, const void *b) {
    const WordEntry *entry_a = (const WordEntry *)a;
    const WordEntry *entry_b = (const WordEntry *)b;
    if (entry_a->count < entry_b->count) return 1;
    if (entry_a->count > entry_b->count) return -1;
    return 0;
}

void find_n_most_common_words(const char *text, int n) {
    if (text == NULL || n <= 0) {
        return;
    }

    char *current_word = malloc(MAX_WORD_LEN);
    if (!current_word) {
        return;
    }
    int current_word_len = 0;
    num_entries = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha((unsigned char)text[i])) {
            if (current_word_len < MAX_WORD_LEN - 1) {
                current_word[current_word_len++] = tolower((unsigned char)text[i]);
            }
        } else {
            if (current_word_len > 0) {
                current_word[current_word_len] = '\0';
                if (find_or_add_word(current_word) == -1) {
                    break;
                }
                current_word_len = 0;
            }
        }
    }

    if (current_word_len > 0) {
        current_word[current_word_len] = '\0';
        find_or_add_word(current_word);
    }

    free(current_word);

    qsort(word_entries, num_entries, sizeof(WordEntry), compare_word_entries);

    int limit = n < num_entries ? n : num_entries;
    for (int i = 0; i < limit; i++) {
        printf("%s: %d\n", word_entries[i].word, word_entries[i].count);
    }

    for (int i = 0; i < num_entries; i++) {
        free(word_entries[i].word);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <text> <n>\n", argv[0]);
        return 1;
    }

    const char *text = argv[1];
    char *endptr;
    errno = 0;
    long val = strtol(argv[2], &endptr, 10);

    if (endptr == argv[2] || *endptr != '\0' || errno == ERANGE || val <= 0 || val > INT_MAX) {
        fprintf(stderr, "Error: n must be a positive integer within valid range.\n");
        return 1;
    }

    int n = (int)val;

    find_n_most_common_words(text, n);
    
    free(word_entries);
    return 0;
}
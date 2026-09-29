#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 256
#define MAX_WORDS 100000

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

static WordEntry word_entries[MAX_WORDS];
static int num_entries = 0;

int find_or_add_word(const char *word) {
    if (word == NULL || num_entries >= MAX_WORDS) {
        return -1;
    }
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(word_entries[i].word, word) == 0) {
            word_entries[i].count++;
            return i;
        }
    }
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(word_entries[num_entries].word, word, MAX_WORD_LEN - 1);
    word_entries[num_entries].word[MAX_WORD_LEN - 1] = '\0';
    word_entries[num_entries].count = 1;
    num_entries++;
    return num_entries - 1;
}

int compare_word_entries(const void *a, const void *b) {
    const WordEntry *entry_a = (const WordEntry *)a;
    const WordEntry *entry_b = (const WordEntry *)b;
    return entry_b->count - entry_a->count;
}

void find_n_most_common_words(const char *text, int n) {
    if (text == NULL || n <= 0) {
        return;
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current_word[MAX_WORD_LEN];
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

    qsort(word_entries, num_entries, sizeof(WordEntry), compare_word_entries);

    int limit = n < num_entries ? n : num_entries;
    for (int i = 0; i < limit; i++) {
        printf("%s: %d\n", word_entries[i].word, word_entries[i].count);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <text> <n>\n", argv[0]);
        return 1;
    }

    const char *text = argv[1];
    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int n = atoi(argv[2]);

    if (n <= 0) {
        fprintf(stderr, "Error: n must be a positive integer.\n");
        return 1;
    }

    find_n_most_common_words(text, n);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100000
#define MAX_WORD_LEN 256

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

WordEntry *entries = NULL;
int num_entries = 0;
int capacity = 0;

int find_word(const char *word) {
    for (int i = 0; i < num_entries; i++) {
        if (strcmp(entries[i].word, word) == 0) {
            return i;
        }
    }
    return -1;
}

int cmp_entries(const void *a, const void *b) {
    const WordEntry *ea = (const WordEntry *)a;
    const WordEntry *eb = (const WordEntry *)b;
    if (ea->count > eb->count) return -1;
    if (ea->count < eb->count) return 1;
    return strcmp(ea->word, eb->word);
}

void process_text(const char *text, int n) {
    const char *p = text;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char current[MAX_WORD_LEN];

    while (*p) {
        while (*p && !isalpha((unsigned char)*p)) {
            p++;
        }
        if (!*p) {
            break;
        }

        int len = 0;
        while (*p && isalpha((unsigned char)*p)) {
            if (len < MAX_WORD_LEN - 1) {
                current[len++] = (char)tolower((unsigned char)*p);
            }
            p++;
        }
        current[len] = '\0';

        if (len > 0) {
            int idx = find_word(current);
            if (idx != -1) {
                entries[idx].count++;
            } else {
                if (num_entries >= capacity) {
                    int new_capacity = capacity == 0 ? 1024 : capacity * 2;
                    if (new_capacity > MAX_WORDS) new_capacity = MAX_WORDS;
                    if (num_entries >= MAX_WORDS) break;
                    WordEntry *new_entries = realloc(entries, (size_t)new_capacity * sizeof(WordEntry));
                    if (!new_entries) break;
                    entries = new_entries;
                    capacity = new_capacity;
                }
                if (num_entries < capacity) {
                    /* Possible weaknesses found:
                     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                     */
                    strncpy(entries[num_entries].word, current, MAX_WORD_LEN - 1);
                    entries[num_entries].word[MAX_WORD_LEN - 1] = '\0';
                    entries[num_entries].count = 1;
                    num_entries++;
                }
            }
        }
    }

    qsort(entries, num_entries, sizeof(WordEntry), cmp_entries);

    int limit = n < num_entries ? n : num_entries;
    for (int i = 0; i < limit; i++) {
        printf("%s: %d\n", entries[i].word, entries[i].count);
    }
}

int main(void) {
    const char *text = "Hello world! This is a test. Hello again in this world.";
    int n = 3;
    
    process_text(text, n);
    
    free(entries);
    
    return 0;
}
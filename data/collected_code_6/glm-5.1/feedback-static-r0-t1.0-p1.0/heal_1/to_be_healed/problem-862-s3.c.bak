#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100000
#define MAX_WORD_LEN 256

typedef struct {
    char word[MAX_WORD_LEN];
    int count;
} WordEntry;

WordEntry entries[MAX_WORDS];
int num_entries = 0;

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
    return eb->count - ea->count;
}

void process_text(const char *text, int n) {
    const char *p = text;
    char current[MAX_WORD_LEN];
    /* Possible weaknesses found:
     *  The scope of the variable 'idx' can be reduced. [variableScope]
     */
    int idx;

    while (*p) {
        while (*p && !isalpha(*p)) {
            p++;
        }
        if (!*p) {
            break;
        }

        int len = 0;
        while (*p && isalpha(*p)) {
            if (len < MAX_WORD_LEN - 1) {
                current[len++] = tolower(*p);
            }
            p++;
        }
        current[len] = '\0';

        idx = find_word(current);
        if (idx != -1) {
            entries[idx].count++;
        } else {
            if (num_entries < MAX_WORDS) {
                strcpy(entries[num_entries].word, current);
                entries[num_entries].count = 1;
                num_entries++;
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
    
    return 0;
}
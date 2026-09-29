#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_WORD_LEN 128
#define TOP_COUNT 10

typedef struct {
    char *word;
    size_t count;
} WordEntry;

typedef struct {
    WordEntry *entries;
    size_t size;
    size_t capacity;
} WordTable;

static int word_table_init(WordTable *table)
{
    table->size = 0;
    table->capacity = 64;
    table->entries = malloc(table->capacity * sizeof(WordEntry));
    if (table->entries == NULL) {
        table->capacity = 0;
        return -1;
    }
    return 0;
}

static void word_table_free(WordTable *table)
{
    size_t i;

    if (table == NULL || table->entries == NULL) {
        return;
    }
    for (i = 0; i < table->size; i++) {
        free(table->entries[i].word);
    }
    free(table->entries);
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

static int word_table_grow(WordTable *table)
{
    WordEntry *new_entries;
    size_t new_capacity;

    if (table->capacity > SIZE_MAX / (2 * sizeof(WordEntry))) {
        return -1;
    }
    new_capacity = table->capacity * 2;
    new_entries = realloc(table->entries, new_capacity * sizeof(WordEntry));
    if (new_entries == NULL) {
        return -1;
    }
    table->entries = new_entries;
    table->capacity = new_capacity;
    return 0;
}

static int word_table_add(WordTable *table, const char *word, size_t word_len)
{
    size_t i;
    char *copy;

    if (word == NULL || word_len == 0 || word_len >= MAX_WORD_LEN) {
        return -1;
    }

    for (i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].word, word) == 0) {
            if (table->entries[i].count == SIZE_MAX) {
                return -1;
            }
            table->entries[i].count++;
            return 0;
        }
    }

    if (table->size == table->capacity) {
        if (word_table_grow(table) != 0) {
            return -1;
        }
    }

    copy = malloc(word_len + 1);
    if (copy == NULL) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, word, word_len);
    copy[word_len] = '\0';

    table->entries[table->size].word = copy;
    table->entries[table->size].count = 1;
    table->size++;
    return 0;
}

static int compare_entries(const void *a, const void *b)
{
    const WordEntry *ea = a;
    const WordEntry *eb = b;

    if (eb->count > ea->count) {
        return 1;
    }
    if (eb->count < ea->count) {
        return -1;
    }
    return strcmp(ea->word, eb->word);
}

static int flush_word(WordTable *table, char *word, size_t *len)
{
    if (*len > 0) {
        if (*len >= MAX_WORD_LEN) {
            return -1;
        }
        word[*len] = '\0';
        if (word_table_add(table, word, *len) != 0) {
            return -1;
        }
        *len = 0;
    }
    return 0;
}

static int count_words(FILE *fp, WordTable *table)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    size_t len = 0;
    int c;
    int overlong = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(fp)) != EOF) {
        if (isalpha((unsigned char)c)) {
            if (overlong) {
                continue;
            }
            if (len < MAX_WORD_LEN - 1) {
                word[len] = (char)tolower((unsigned char)c);
                len++;
            } else {
                overlong = 1;
                len = 0;
            }
        } else {
            if (overlong) {
                overlong = 0;
                continue;
            }
            if (flush_word(table, word, &len) != 0) {
                return -1;
            }
        }
    }

    if (!overlong && flush_word(table, word, &len) != 0) {
        return -1;
    }

    if (ferror(fp)) {
        return -1;
    }
    return 0;
}

static void print_top_words(const WordTable *table, size_t top_n)
{
    size_t i;
    size_t limit;

    limit = table->size < top_n ? table->size : top_n;
    for (i = 0; i < limit; i++) {
        printf("%zu %s\n", table->entries[i].count, table->entries[i].word);
    }
}

int main(int argc, char const *const argv[])
{
    FILE *fp;
    WordTable table;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dictionary-file>\n",
                argv[0] != NULL ? argv[0] : "wordcount");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fopen: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "Error: cannot open file '%s'\n", argv[1]);
        return EXIT_FAILURE;
    }

    if (word_table_init(&table) != 0) {
        fprintf(stderr, "Error: memory allocation failed\n");
        if (fclose(fp) != 0) {
            fprintf(stderr, "Error: failed to close file\n");
        }
        return EXIT_FAILURE;
    }

    if (count_words(fp, &table) != 0) {
        fprintf(stderr, "Error: failed while reading words\n");
        status = EXIT_FAILURE;
    } else {
        if (table.size > 0) {
            qsort(table.entries, table.size, sizeof(WordEntry),
                  compare_entries);
        }
        print_top_words(&table, TOP_COUNT);
    }

    word_table_free(&table);

    if (fclose(fp) != 0) {
        fprintf(stderr, "Error: failed to close file\n");
        status = EXIT_FAILURE;
    }

    return status;
}
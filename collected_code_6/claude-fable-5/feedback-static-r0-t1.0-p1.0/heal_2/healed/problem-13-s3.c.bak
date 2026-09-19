#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

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

static int word_table_add(WordTable *table, const char *word)
{
    size_t i;
    char *copy;
    WordEntry *new_entries;

    for (i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].word, word) == 0) {
            table->entries[i].count++;
            return 0;
        }
    }

    if (table->size == table->capacity) {
        if (table->capacity > SIZE_MAX / (2 * sizeof(WordEntry))) {
            return -1;
        }
        new_entries = realloc(table->entries,
                              table->capacity * 2 * sizeof(WordEntry));
        if (new_entries == NULL) {
            return -1;
        }
        table->entries = new_entries;
        table->capacity *= 2;
    }

    copy = malloc(strlen(word) + 1);
    if (copy == NULL) {
        return -1;
    }
    strcpy(copy, word);

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

static int count_words(FILE *fp, WordTable *table)
{
    char word[MAX_WORD_LEN];
    size_t len = 0;

    for (;;) {
        int c = fgetc(fp);

        if (c != EOF && isalpha((unsigned char)c)) {
            if (len < MAX_WORD_LEN - 1) {
                word[len] = (char)tolower((unsigned char)c);
                len++;
            }
        } else {
            if (len > 0) {
                word[len] = '\0';
                if (word_table_add(table, word) != 0) {
                    return -1;
                }
                len = 0;
            }
            if (c == EOF) {
                break;
            }
        }
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

int main(int argc, const char *const argv[])
{
    FILE *fp;
    WordTable table;
    int status = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dictionary-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

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
        qsort(table.entries, table.size, sizeof(WordEntry), compare_entries);
        print_top_words(&table, TOP_COUNT);
    }

    word_table_free(&table);

    if (fclose(fp) != 0) {
        fprintf(stderr, "Error: failed to close file\n");
        status = EXIT_FAILURE;
    }

    return status;
}
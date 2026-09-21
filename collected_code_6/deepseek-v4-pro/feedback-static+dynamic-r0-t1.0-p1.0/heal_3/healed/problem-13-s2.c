#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdint.h>

#define MAX_WORD_LEN 128
#define INITIAL_CAPACITY 128
#define MAX_LINE_LEN (MAX_WORD_LEN * 1024)

typedef struct {
    char *word;
    int count;
} WordEntry;

typedef struct {
    WordEntry *entries;
    size_t size;
    size_t capacity;
} WordTable;

static void init_table(WordTable *table) {
    table->capacity = INITIAL_CAPACITY;
    table->size = 0;
    table->entries = malloc(table->capacity * sizeof(WordEntry));
    if (!table->entries) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}

static void free_table(WordTable *table) {
    if (table->entries) {
        for (size_t i = 0; i < table->size; i++) {
            free(table->entries[i].word);
        }
        free(table->entries);
        table->entries = NULL;
    }
    table->size = 0;
    table->capacity = 0;
}

static char *duplicate_word(const char *word) {
    size_t len = 0;
    while (len < MAX_WORD_LEN && word[len] != '\0') {
        len++;
    }
    char *copy = malloc(len + 1);
    if (!copy) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < len; i++) {
        copy[i] = word[i];
    }
    copy[len] = '\0';
    return copy;
}

static int find_word(const WordTable *table, const char *word) {
    for (size_t i = 0; i < table->size; i++) {
        if (strcmp(table->entries[i].word, word) == 0) {
            return (int)i;
        }
    }
    return -1;
}

static void add_word(WordTable *table, const char *word) {
    int index = find_word(table, word);
    if (index >= 0) {
        table->entries[index].count++;
        return;
    }

    if (table->size == table->capacity) {
        if (table->capacity > SIZE_MAX / 2 / sizeof(WordEntry)) {
            fprintf(stderr, "Table capacity overflow\n");
            exit(EXIT_FAILURE);
        }
        size_t new_capacity = table->capacity * 2;
        WordEntry *new_entries = realloc(table->entries, new_capacity * sizeof(WordEntry));
        if (!new_entries) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        table->entries = new_entries;
        table->capacity = new_capacity;
    }

    table->entries[table->size].word = duplicate_word(word);
    table->entries[table->size].count = 1;
    table->size++;
}

static void normalize_word(char *word) {
    size_t len = 0;
    while (word[len] != '\0') {
        len++;
    }
    while (len > 0 && (ispunct((unsigned char)word[len - 1]) ||
                       isspace((unsigned char)word[len - 1]))) {
        word[len - 1] = '\0';
        len--;
    }
}

static void process_text(WordTable *table, const char *text) {
    char buffer[MAX_WORD_LEN];
    size_t pos = 0;
    size_t i = 0;

    while (text[i] != '\0') {
        if (isalnum((unsigned char)text[i]) || text[i] == '\'') {
            if (pos < MAX_WORD_LEN - 1) {
                buffer[pos++] = tolower((unsigned char)text[i]);
            }
        } else if (pos > 0) {
            buffer[pos] = '\0';
            normalize_word(buffer);
            if (buffer[0] != '\0') {
                add_word(table, buffer);
            }
            pos = 0;
        }
        i++;
    }

    if (pos > 0) {
        buffer[pos] = '\0';
        normalize_word(buffer);
        if (buffer[0] != '\0') {
            add_word(table, buffer);
        }
    }
}

static int compare_entries(const void *a, const void *b) {
    const WordEntry *entry_a = (const WordEntry *)a;
    const WordEntry *entry_b = (const WordEntry *)b;
    if (entry_b->count != entry_a->count) {
        return entry_b->count - entry_a->count;
    }
    return strcmp(entry_a->word, entry_b->word);
}

static void print_most_common(const WordTable *table, int top_n) {
    size_t count = table->size < (size_t)top_n ? table->size : (size_t)top_n;
    for (size_t i = 0; i < count; i++) {
        printf("%s: %d\n", table->entries[i].word, table->entries[i].count);
    }
}

void count_most_common_words(const char *filename, int top_n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return;
    }

    WordTable table;
    init_table(&table);

    char line_buffer[MAX_LINE_LEN];

    while (fgets(line_buffer, sizeof(line_buffer), file)) {
        size_t len = 0;
        while (line_buffer[len] != '\0') {
            len++;
        }
        if (len > 0 && line_buffer[len - 1] == '\n') {
            line_buffer[len - 1] = '\0';
        }
        process_text(&table, line_buffer);
    }

    if (ferror(file)) {
        fprintf(stderr, "Error reading file: %s\n", filename);
    }

    fclose(file);

    qsort(table.entries, table.size, sizeof(WordEntry), compare_entries);

    print_most_common(&table, top_n);

    free_table(&table);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [top_n]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    int top_n = 10;

    if (argc >= 3) {
        char *endptr;
        errno = 0;
        long value = strtol(argv[2], &endptr, 10);
        if (errno == 0 && *endptr == '\0' && value > 0 && value <= 1000) {
            top_n = (int)value;
        } else {
            fprintf(stderr, "Invalid top_n value, using default 10\n");
        }
    }

    count_most_common_words(filename, top_n);

    return EXIT_SUCCESS;
}
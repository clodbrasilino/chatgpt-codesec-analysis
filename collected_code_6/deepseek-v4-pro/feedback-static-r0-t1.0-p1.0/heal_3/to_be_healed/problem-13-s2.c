#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 256
#define INITIAL_CAPACITY 128

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
    for (size_t i = 0; i < table->size; i++) {
        free(table->entries[i].word);
    }
    free(table->entries);
    table->entries = NULL;
    table->size = 0;
    table->capacity = 0;
}

static char *duplicate_word(const char *word) {
    size_t len = strnlen(word, MAX_WORD_LEN);
    char *copy = malloc(len + 1);
    if (!copy) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, word, len);
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
        size_t new_capacity = table->capacity * 2;
        if (new_capacity < table->capacity) {
            fprintf(stderr, "Capacity overflow\n");
            exit(EXIT_FAILURE);
        }
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(word);
    while (len > 0 && (ispunct((unsigned char)word[len - 1]) ||
                       isspace((unsigned char)word[len - 1]))) {
        word[len - 1] = '\0';
        len--;
    }
}

static int is_word_char(int c) {
    return isalnum(c) || c == '\'';
}

static void process_text(WordTable *table, const char *text) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_WORD_LEN];
    size_t pos = 0;
    size_t i = 0;

    while (text[i] != '\0') {
        unsigned char c = (unsigned char)text[i];
        if (is_word_char(c)) {
            if (pos < MAX_WORD_LEN - 1) {
                buffer[pos++] = tolower(c);
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
    size_t count = (table->size < (size_t)top_n) ? table->size : (size_t)top_n;
    for (size_t i = 0; i < count; i++) {
        printf("%s: %d\n", table->entries[i].word, table->entries[i].count);
    }
}

void count_most_common_words(const char *filename, int top_n) {
    /* Possible weaknesses found:
     * Flawfinder fopen: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Cannot open file: %s\n", filename);
        return;
    }

    WordTable table;
    init_table(&table);

    char *line = NULL;
    size_t line_capacity = 0;
    ssize_t line_length;

    while ((line_length = getline(&line, &line_capacity, file)) != -1) {
        if (line_length > 0 && line != NULL) {
            process_text(&table, line);
        }
    }

    free(line);
    fclose(file);

    if (table.size > 0) {
        qsort(table.entries, table.size, sizeof(WordEntry), compare_entries);
    }

    print_most_common(&table, top_n);

    free_table(&table);
}

#ifndef _WIN32
#include <unistd.h>
#else
#include <io.h>
#define F_OK 0
/* Possible weaknesses found:
 * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
 */
#define access _access
#endif

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [top_n]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];

    /* Possible weaknesses found:
     * Flawfinder access: This usually indicates a security flaw. If an attacker can change anything along the path between the call to access() and the file's actual use (e.g., by moving files), the attacker can exploit the race condition (CWE-362/CWE-367!). Set up the correct permissions (e.g., using setuid()) and try to open the file directly. (risk 4, race)
     */
    if (access(filename, F_OK) != 0) {
        fprintf(stderr, "File does not exist or is not accessible: %s\n", filename);
        return EXIT_FAILURE;
    }

    int top_n = 10;

    if (argc >= 3) {
        char *endptr;
        long value = strtol(argv[2], &endptr, 10);
        if (*endptr == '\0' && value > 0 && value <= 1000) {
            top_n = (int)value;
        } else {
            fprintf(stderr, "Invalid top_n value, using default 10\n");
        }
    }

    count_most_common_words(filename, top_n);

    return EXIT_SUCCESS;
}
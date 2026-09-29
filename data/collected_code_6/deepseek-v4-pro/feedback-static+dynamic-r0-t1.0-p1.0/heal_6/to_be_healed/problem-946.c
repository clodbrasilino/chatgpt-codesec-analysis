#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 256
#define INITIAL_CAPACITY 64
#define HASH_SIZE 1009

typedef struct WordCount {
    char *word;
    int count;
    struct WordCount *next;
} WordCount;

typedef struct {
    WordCount *buckets[HASH_SIZE];
    int total_words;
} WordTable;

unsigned int hash_word(const char *word) {
    unsigned int hash = 5381;
    int c;
    while ((c = (unsigned char)*word++) != '\0') {
        hash = ((hash << 5) + hash) + tolower(c);
    }
    return hash % HASH_SIZE;
}

WordTable *create_word_table(void) {
    WordTable *table = (WordTable *)calloc(1, sizeof(WordTable));
    if (!table) {
        return NULL;
    }
    return table;
}

void add_word_to_table(WordTable *table, const char *word) {
    if (!table || !word) {
        return;
    }

    size_t word_len = strnlen(word, MAX_WORD_LEN);
    if (word_len >= MAX_WORD_LEN) {
        return;
    }
    
    unsigned int index = hash_word(word);
    WordCount *entry = table->buckets[index];
    
    while (entry) {
        if (strcasecmp(entry->word, word) == 0) {
            entry->count++;
            return;
        }
        entry = entry->next;
    }
    
    entry = (WordCount *)calloc(1, sizeof(WordCount));
    if (!entry) {
        return;
    }
    
    entry->word = strndup(word, word_len);
    if (!entry->word) {
        free(entry);
        return;
    }
    entry->count = 1;
    entry->next = table->buckets[index];
    table->buckets[index] = entry;
    table->total_words++;
}

void free_word_table(WordTable *table) {
    if (!table) {
        return;
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        WordCount *entry = table->buckets[i];
        while (entry) {
            WordCount *next = entry->next;
            free(entry->word);
            free(entry);
            entry = next;
        }
    }
    free(table);
}

void find_most_common_elements(const char *text) {
    if (!text) {
        fprintf(stderr, "Error: NULL input text\n");
        return;
    }
    
    WordTable *table = create_word_table();
    if (!table) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        return;
    }
    
    char *current_word = (char *)malloc(MAX_WORD_LEN);
    if (!current_word) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
        free_word_table(table);
        return;
    }
    
    size_t text_len = strnlen(text, SIZE_MAX);
    size_t word_len = 0;
    
    for (size_t i = 0; i < text_len; i++) {
        unsigned char c = (unsigned char)text[i];
        if (isalnum(c) || c == '_' || c == '-') {
            if (word_len < MAX_WORD_LEN - 1) {
                current_word[word_len++] = (char)tolower(c);
            }
        } else {
            if (word_len > 0) {
                current_word[word_len] = '\0';
                add_word_to_table(table, current_word);
                word_len = 0;
            }
        }
    }
    
    if (word_len > 0) {
        current_word[word_len] = '\0';
        add_word_to_table(table, current_word);
    }
    
    free(current_word);
    
    int max_count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        WordCount *entry = table->buckets[i];
        while (entry) {
            if (entry->count > max_count) {
                max_count = entry->count;
            }
            entry = entry->next;
        }
    }
    
    if (max_count == 0) {
        printf("No words found in the text.\n");
        free_word_table(table);
        return;
    }
    
    printf("Most common element(s) with count %d:\n", max_count);
    for (int i = 0; i < HASH_SIZE; i++) {
        WordCount *entry = table->buckets[i];
        while (entry) {
            if (entry->count == max_count) {
                printf("  %d: %s\n", entry->count, entry->word);
            }
            entry = entry->next;
        }
    }
    
    free_word_table(table);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc > 1) {
        find_most_common_elements(argv[1]);
    } else {
        char *buffer = NULL;
        size_t buffer_size = 0;
        ssize_t bytes_read = getline(&buffer, &buffer_size, stdin);
        
        if (bytes_read == -1) {
            fprintf(stderr, "Error: Failed to read input\n");
            free(buffer);
            return EXIT_FAILURE;
        }
        
        if (bytes_read > 0 && buffer[bytes_read - 1] == '\n') {
            buffer[bytes_read - 1] = '\0';
        }
        
        find_most_common_elements(buffer);
        free(buffer);
    }
    
    return EXIT_SUCCESS;
}
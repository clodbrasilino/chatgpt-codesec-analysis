#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_SIZE 10007
#define INITIAL_WORD_CAPACITY 256

typedef struct WordNode {
    char *word;
    int count;
    struct WordNode *next;
} WordNode;

typedef struct {
    WordNode *buckets[HASH_SIZE];
} HashTable;

unsigned int hash(const char *word) {
    unsigned int hash_value = 5381;
    int c;
    while ((c = *word++)) {
        hash_value = ((hash_value << 5) + hash_value) + c;
    }
    return hash_value % HASH_SIZE;
}

HashTable* create_table(void) {
    HashTable *table = malloc(sizeof(HashTable));
    if (!table) return NULL;
    for (int i = 0; i < HASH_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

int insert_word(HashTable *table, const char *word, size_t len) {
    if (!table || !word) return -1;
    unsigned int idx = hash(word);
    WordNode *curr = table->buckets[idx];
    
    while (curr) {
        if (strcmp(curr->word, word) == 0) {
            curr->count++;
            return 0;
        }
        curr = curr->next;
    }
    
    WordNode *new_node = malloc(sizeof(WordNode));
    if (!new_node) return -1;
    
    new_node->word = malloc(len + 1);
    if (!new_node->word) {
        free(new_node);
        return -1;
    }
    
    memcpy(new_node->word, word, len);
    new_node->word[len] = '\0';
    
    new_node->count = 1;
    new_node->next = table->buckets[idx];
    table->buckets[idx] = new_node;
    
    return 0;
}

void free_table(HashTable *table) {
    if (!table) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        WordNode *curr = table->buckets[i];
        while (curr) {
            WordNode *temp = curr;
            curr = curr->next;
            free(temp->word);
            free(temp);
        }
    }
    free(table);
}

void process_file(const char *filename, HashTable *table) {
    FILE *file = fopen(filename, "r");
    if (!file) return;
    
    size_t capacity = INITIAL_WORD_CAPACITY;
    char *word = malloc(capacity);
    if (!word) {
        fclose(file);
        return;
    }
    
    size_t len = 0;
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            if (len >= capacity - 1) {
                size_t new_capacity = capacity * 2;
                if (new_capacity < capacity) {
                    free(word);
                    fclose(file);
                    return;
                }
                char *new_word = realloc(word, new_capacity);
                if (!new_word) {
                    free(word);
                    fclose(file);
                    return;
                }
                word = new_word;
                capacity = new_capacity;
            }
            word[len++] = (char)tolower(c);
        } else {
            if (len > 0) {
                word[len] = '\0';
                insert_word(table, word, len);
                len = 0;
            }
        }
    }
    
    if (len > 0) {
        word[len] = '\0';
        insert_word(table, word, len);
    }
    
    free(word);
    fclose(file);
}

void find_most_common(HashTable *table, char **most_common_word, int *max_count) {
    *max_count = 0;
    *most_common_word = NULL;
    
    if (!table) return;
    
    for (int i = 0; i < HASH_SIZE; i++) {
        WordNode *curr = table->buckets[i];
        while (curr) {
            if (curr->count > *max_count) {
                *max_count = curr->count;
                *most_common_word = curr->word;
            }
            curr = curr->next;
        }
    }
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <dictionary_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    HashTable *table = create_table();
    if (!table) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    
    process_file(argv[1], table);
    
    char *most_common_word = NULL;
    int max_count = 0;
    
    find_most_common(table, &most_common_word, &max_count);
    
    if (most_common_word) {
        printf("Most common word: %s (%d occurrences)\n", most_common_word, max_count);
    } else {
        printf("No words found.\n");
    }
    
    free_table(table);
    
    return EXIT_SUCCESS;
}
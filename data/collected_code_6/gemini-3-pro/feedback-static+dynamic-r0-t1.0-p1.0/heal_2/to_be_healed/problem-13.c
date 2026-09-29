#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 256
#define HASH_SIZE 10007

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

int insert_word(HashTable *table, const char *word) {
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
    
    new_node->word = strdup(word);
    if (!new_node->word) {
        free(new_node);
        return -1;
    }
    
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
    /* Possible weaknesses found:
     * Flawfinder fopen: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    FILE *file = fopen(filename, "r");
    if (!file) return;
    
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char word[MAX_WORD_LEN];
    int len = 0;
    int c;
    
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(file)) != EOF) {
        if (isalpha(c)) {
            if (len < MAX_WORD_LEN - 1) {
                word[len++] = (char)tolower(c);
            }
        } else {
            if (len > 0) {
                word[len] = '\0';
                insert_word(table, word);
                len = 0;
            }
        }
    }
    if (len > 0) {
        word[len] = '\0';
        insert_word(table, word);
    }
    
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
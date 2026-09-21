#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef O_NOFOLLOW
#define O_NOFOLLOW 0
#endif

#ifndef O_CLOEXEC
#define O_CLOEXEC 0
#endif

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
    unsigned int hashValue = 0;
    while (*word) {
        hashValue = (hashValue * 31) + (unsigned char)(*word);
        word++;
    }
    return hashValue % HASH_SIZE;
}

HashTable* create_table() {
    HashTable *table = calloc(1, sizeof(HashTable));
    return table;
}

void insert_word(HashTable *table, const char *word) {
    if (!table || !word) return;
    unsigned int index = hash(word);
    WordNode *current = table->buckets[index];
    
    while (current) {
        if (strcmp(current->word, word) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }
    
    WordNode *new_node = malloc(sizeof(WordNode));
    if (!new_node) return;
    
    new_node->word = strdup(word);
    if (!new_node->word) {
        free(new_node);
        return;
    }
    
    new_node->count = 1;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
}

void free_table(HashTable *table) {
    if (!table) return;
    for (int i = 0; i < HASH_SIZE; i++) {
        WordNode *current = table->buckets[i];
        while (current) {
            WordNode *temp = current;
            current = current->next;
            free(temp->word);
            free(temp);
        }
    }
    free(table);
}

void find_most_common(HashTable *table, char **most_common_word, int *max_count) {
    if (!table || !most_common_word || !max_count) return;
    
    *max_count = 0;
    *most_common_word = NULL;
    
    for (int i = 0; i < HASH_SIZE; i++) {
        WordNode *current = table->buckets[i];
        while (current) {
            if (current->count > *max_count) {
                *max_count = current->count;
                *most_common_word = current->word;
            }
            current = current->next;
        }
    }
}

void process_file(const char *filename, HashTable *table) {
    if (!filename || !table) return;
    
    /* Possible weaknesses found:
     * Flawfinder open: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    int fd = open(filename, O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd == -1) {
        fprintf(stderr, "Error opening file securely.\n");
        return;
    }
    
    FILE *file = fdopen(fd, "r");
    if (!file) {
        close(fd);
        fprintf(stderr, "Error associating stream with file descriptor.\n");
        return;
    }
    
    size_t capacity = 256;
    char *clean_word = malloc(capacity);
    if (!clean_word) {
        fclose(file);
        return;
    }
    
    size_t j = 0;
    int c;
    
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(file)) != EOF) {
        if (isalpha((unsigned char)c)) {
            if (j + 1 >= capacity) {
                size_t new_capacity = capacity * 2;
                char *temp = realloc(clean_word, new_capacity);
                if (!temp) {
                    break;
                }
                capacity = new_capacity;
                clean_word = temp;
            }
            clean_word[j++] = tolower((unsigned char)c);
        } else if (j > 0) {
            clean_word[j] = '\0';
            insert_word(table, clean_word);
            j = 0;
        }
    }
    
    if (j > 0) {
        clean_word[j] = '\0';
        insert_word(table, clean_word);
    }
    
    free(clean_word);
    fclose(file);
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <dictionary_file>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    HashTable *table = create_table();
    if (!table) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }
    
    process_file(argv[1], table);
    
    char *most_common = NULL;
    int max_count = 0;
    
    find_most_common(table, &most_common, &max_count);
    
    if (most_common) {
        printf("Most common word: %s (Count: %d)\n", most_common, max_count);
    } else {
        printf("No words found.\n");
    }
    
    free_table(table);
    return EXIT_SUCCESS;
}
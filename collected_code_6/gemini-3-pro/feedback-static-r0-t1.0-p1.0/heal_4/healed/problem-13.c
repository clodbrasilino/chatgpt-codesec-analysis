#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

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
    HashTable *table = calloc(1, sizeof(HashTable));
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
    int fd = open(filename, O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd == -1) return;
    
    struct stat st;
    if (fstat(fd, &st) != 0 || !S_ISREG(st.st_mode)) {
        close(fd);
        return;
    }
    
    FILE *file = fdopen(fd, "r");
    if (!file) {
        close(fd);
        return;
    }
    
    size_t capacity = MAX_WORD_LEN;
    char *word = malloc(capacity);
    if (!word) {
        fclose(file);
        return;
    }

    size_t char_idx = 0;
    char buffer[4096];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        for (size_t i = 0; i < bytes_read; i++) {
            int c = buffer[i];
            if (isalpha((unsigned char)c)) {
                if (char_idx >= capacity - 1) {
                    size_t new_capacity = capacity * 2;
                    char *new_word = realloc(word, new_capacity);
                    if (!new_word) {
                        free(word);
                        fclose(file);
                        return;
                    }
                    word = new_word;
                    capacity = new_capacity;
                }
                word[char_idx++] = (char)tolower((unsigned char)c);
            } else {
                if (char_idx > 0) {
                    word[char_idx] = '\0';
                    insert_word(table, word);
                    char_idx = 0;
                }
            }
        }
    }
    
    if (char_idx > 0) {
        word[char_idx] = '\0';
        insert_word(table, word);
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

int main(int argc, const char * const argv[]) {
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
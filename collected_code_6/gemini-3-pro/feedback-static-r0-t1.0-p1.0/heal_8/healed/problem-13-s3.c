#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>
#include <sys/stat.h>

#define HASH_SIZE 10007
#define MAX_WORD_LENGTH 8192

#ifndef O_NOFOLLOW
#define O_NOFOLLOW 0
#endif

#ifndef O_CLOEXEC
#define O_CLOEXEC 0
#endif

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
        hashValue = (hashValue * 31) + tolower((unsigned char)*word);
        word++;
    }
    return hashValue % HASH_SIZE;
}

HashTable* create_table(void) {
    HashTable *table = malloc(sizeof(HashTable));
    if (!table) return NULL;
    for (int i = 0; i < HASH_SIZE; i++) {
        table->buckets[i] = NULL;
    }
    return table;
}

void insert_word(HashTable *table, const char *word) {
    if (!table || !word) return;
    unsigned int index = hash(word);
    WordNode *current = table->buckets[index];
    
    while (current) {
        if (strcasecmp(current->word, word) == 0) {
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
    
    int fd = open(filename, O_RDONLY | O_NOFOLLOW | O_CLOEXEC);
    if (fd == -1) {
        fprintf(stderr, "Error opening file.\n");
        return;
    }

    struct stat st;
    if (fstat(fd, &st) == -1 || !S_ISREG(st.st_mode)) {
        fprintf(stderr, "Invalid file type.\n");
        close(fd);
        return;
    }

    FILE *file = fdopen(fd, "r");
    if (!file) {
        fprintf(stderr, "Error opening file stream.\n");
        close(fd);
        return;
    }
    
    size_t capacity = 256;
    char *word = malloc(capacity);
    if (!word) {
        fprintf(stderr, "Memory allocation failed.\n");
        fclose(file);
        return;
    }

    size_t length = 0;
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        if (isalpha((unsigned char)c)) {
            if (length + 1 >= capacity) {
                if (capacity >= MAX_WORD_LENGTH) {
                    continue;
                }
                size_t new_capacity = capacity * 2;
                if (new_capacity > MAX_WORD_LENGTH) {
                    new_capacity = MAX_WORD_LENGTH;
                }
                char *new_word = realloc(word, new_capacity);
                if (!new_word) {
                    fprintf(stderr, "Memory reallocation failed.\n");
                    free(word);
                    fclose(file);
                    return;
                }
                word = new_word;
                capacity = new_capacity;
            }
            word[length++] = tolower((unsigned char)c);
        } else {
            if (length > 0) {
                word[length] = '\0';
                insert_word(table, word);
                length = 0;
            }
        }
    }
    
    if (length > 0) {
        word[length] = '\0';
        insert_word(table, word);
    }
    
    free(word);
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
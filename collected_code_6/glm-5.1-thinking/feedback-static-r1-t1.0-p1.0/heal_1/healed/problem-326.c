#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_TABLE_SIZE 1021

typedef struct Node {
    char *word;
    size_t wlen;
    int count;
    struct Node *next;
} Node;

typedef struct {
    Node *buckets[HASH_TABLE_SIZE];
} HashTable;

static unsigned long hash_string(const char *str, size_t len) {
    unsigned long hash = 5381;
    for (size_t i = 0; i < len; i++) {
        hash = ((hash << 5) + hash) + (unsigned char)str[i];
    }
    return hash % HASH_TABLE_SIZE;
}

static HashTable *create_hash_table(void) {
    HashTable *table = malloc(sizeof(HashTable));
    if (!table) {
        return NULL;
    }
    memset(table->buckets, 0, sizeof(table->buckets));
    return table;
}

static void free_hash_table(HashTable *table) {
    if (!table) {
        return;
    }
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node *current = table->buckets[i];
        while (current) {
            Node *next = current->next;
            free(current->word);
            free(current);
            current = next;
        }
    }
    free(table);
}

static int add_word(HashTable *table, const char *word, size_t wlen) {
    unsigned long index = hash_string(word, wlen);
    Node *current = table->buckets[index];
    while (current) {
        if (current->wlen == wlen) {
            int match = 1;
            for (size_t i = 0; i < wlen; i++) {
                if (current->word[i] != word[i]) {
                    match = 0;
                    break;
                }
            }
            if (match) {
                current->count++;
                return 0;
            }
        }
        current = current->next;
    }
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        return -1;
    }
    new_node->word = malloc(wlen + 1);
    if (!new_node->word) {
        free(new_node);
        return -1;
    }
    for (size_t i = 0; i < wlen; i++) {
        new_node->word[i] = word[i];
    }
    new_node->word[wlen] = '\0';
    new_node->wlen = wlen;
    new_node->count = 1;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    return 0;
}

char *get_most_frequent_word(char **strings, int count) {
    if (!strings || count <= 0) {
        return NULL;
    }
    HashTable *table = create_hash_table();
    if (!table) {
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        if (!strings[i]) {
            continue;
        }
        const char *ptr = strings[i];
        while (*ptr) {
            while (*ptr && !isalpha((unsigned char)*ptr)) {
                ptr++;
            }
            if (!*ptr) {
                break;
            }
            const char *start = ptr;
            while (*ptr && isalpha((unsigned char)*ptr)) {
                ptr++;
            }
            size_t len = (size_t)(ptr - start);
            if (add_word(table, start, len) != 0) {
                free_hash_table(table);
                return NULL;
            }
        }
    }
    int max_count = 0;
    char *result = NULL;
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
        Node *current = table->buckets[i];
        while (current) {
            if (current->count > max_count) {
                max_count = current->count;
                free(result);
                result = malloc(current->wlen + 1);
                if (!result) {
                    free_hash_table(table);
                    return NULL;
                }
                for (size_t j = 0; j < current->wlen; j++) {
                    result[j] = current->word[j];
                }
                result[current->wlen] = '\0';
            }
            current = current->next;
        }
    }
    free_hash_table(table);
    return result;
}

int main(void) {
    char *strings[] = {
        "hello world and universe",
        "the world is vast",
        "hello from the other side",
        "world of warcraft",
        "hello world"
    };
    int count = sizeof(strings) / sizeof(strings[0]);
    char *most_frequent = get_most_frequent_word(strings, count);
    if (most_frequent) {
        printf("%s\n", most_frequent);
        free(most_frequent);
    } else {
        printf("No words found.\n");
    }
    return 0;
}
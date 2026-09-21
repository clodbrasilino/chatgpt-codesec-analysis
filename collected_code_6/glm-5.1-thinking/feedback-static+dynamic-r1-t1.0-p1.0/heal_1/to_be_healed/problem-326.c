#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define HASH_TABLE_SIZE 1021

typedef struct Node {
    char *word;
    int count;
    struct Node *next;
} Node;

typedef struct {
    Node *buckets[HASH_TABLE_SIZE];
} HashTable;

static unsigned long hash_string(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
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

static int add_word(HashTable *table, const char *word) {
    unsigned long index = hash_string(word);
    Node *current = table->buckets[index];
    while (current) {
        if (strcmp(current->word, word) == 0) {
            current->count++;
            return 0;
        }
        current = current->next;
    }
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    new_node->word = malloc(strlen(word) + 1);
    if (!new_node->word) {
        free(new_node);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
     */
    strcpy(new_node->word, word);
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
            char *word = malloc(len + 1);
            if (!word) {
                free_hash_table(table);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(word, start, len);
            word[len] = '\0';
            if (add_word(table, word) != 0) {
                free(word);
                free_hash_table(table);
                return NULL;
            }
            free(word);
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
                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 */
                result = malloc(strlen(current->word) + 1);
                if (!result) {
                    free_hash_table(table);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder strcpy: Does not check for buffer overflows when copying to destination [MS-banned] (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy easily misused). (risk 4, buffer)
                 */
                strcpy(result, current->word);
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
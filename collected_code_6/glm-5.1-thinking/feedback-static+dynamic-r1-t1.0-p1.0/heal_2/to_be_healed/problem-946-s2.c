#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1024

typedef struct Node {
    char *word;
    int count;
    struct Node *next;
} Node;

static char *duplicate_string(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(d, s, len);
    }
    return d;
}

static unsigned int hash_str(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + (unsigned int)c;
    }
    return hash % TABLE_SIZE;
}

static Node *create_node(const char *word) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        return NULL;
    }
    node->word = duplicate_string(word);
    if (!node->word) {
        free(node);
        return NULL;
    }
    node->count = 1;
    node->next = NULL;
    return node;
}

static void insert_word(Node **table, const char *word) {
    if (!table || !word) {
        return;
    }
    unsigned int index = hash_str(word);
    Node *current = table[index];
    
    while (current) {
        if (strcmp(current->word, word) == 0) {
            current->count++;
            return;
        }
        current = current->next;
    }
    
    Node *new_node = create_node(word);
    if (new_node) {
        new_node->next = table[index];
        table[index] = new_node;
    }
}

static void free_table(Node **table) {
    if (!table) {
        return;
    }
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = table[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->word);
            free(temp);
        }
        table[i] = NULL;
    }
}

void find_most_common(const char *text) {
    if (!text) {
        return;
    }

    Node *table[TABLE_SIZE];
    memset(table, 0, sizeof(table));

    const char *p = text;
    size_t buf_cap = 256;
    size_t buf_idx = 0;
    char *buffer = malloc(buf_cap);
    if (!buffer) {
        free_table(table);
        return;
    }

    while (*p) {
        if (isalpha((unsigned char)*p)) {
            if (buf_idx >= buf_cap - 1) {
                buf_cap *= 2;
                char *new_buf = realloc(buffer, buf_cap);
                if (!new_buf) {
                    free(buffer);
                    free_table(table);
                    return;
                }
                buffer = new_buf;
            }
            buffer[buf_idx++] = (char)tolower((unsigned char)*p);
        } else {
            if (buf_idx > 0) {
                buffer[buf_idx] = '\0';
                insert_word(table, buffer);
                buf_idx = 0;
            }
        }
        p++;
    }
    
    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        insert_word(table, buffer);
    }

    int max_count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = table[i];
        while (current) {
            if (current->count > max_count) {
                max_count = current->count;
            }
            current = current->next;
        }
    }

    if (max_count > 0) {
        printf("Most common elements and their counts:\n");
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node *current = table[i];
            while (current) {
                if (current->count == max_count) {
                    printf("%s: %d\n", current->word, current->count);
                }
                current = current->next;
            }
        }
    }

    free(buffer);
    free_table(table);
}

int main(void) {
    const char *text = "This is a test. This test is only a test.";
    find_most_common(text);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 4096
#define MAX_TEXT_LEN 1048576

typedef enum {
    SUCCESS,
    ERR_MEMORY,
    ERR_INVALID
} Status;

typedef struct HashNode {
    char *word;
    size_t count;
    struct HashNode *next;
} HashNode;

typedef struct {
    HashNode **buckets;
    size_t size;
    size_t unique_words;
} HashTable;

typedef struct {
    char *word;
    size_t count;
} WordFrequency;

size_t bounded_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

size_t hash_function(const char *str, size_t hash_size) {
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + (unsigned char)c;
    }
    return hash % hash_size;
}

Status init_hash_table(HashTable *ht, size_t size) {
    if (!ht || size == 0) {
        return ERR_INVALID;
    }
    ht->buckets = calloc(size, sizeof(HashNode *));
    if (!ht->buckets) {
        return ERR_MEMORY;
    }
    ht->size = size;
    ht->unique_words = 0;
    return SUCCESS;
}

Status insert_word_hash(HashTable *ht, const char *word) {
    if (!ht || !word) {
        return ERR_INVALID;
    }
    
    size_t idx = hash_function(word, ht->size);
    HashNode *node = ht->buckets[idx];
    
    while (node) {
        if (strncmp(node->word, word, MAX_WORD_LEN) == 0) {
            node->count++;
            return SUCCESS;
        }
        node = node->next;
    }
    
    HashNode *new_node = malloc(sizeof(HashNode));
    if (!new_node) {
        return ERR_MEMORY;
    }
    
    size_t len = bounded_strlen(word, MAX_WORD_LEN);
    new_node->word = malloc(len + 1);
    if (!new_node->word) {
        free(new_node);
        return ERR_MEMORY;
    }
    
    for (size_t i = 0; i < len; i++) {
        new_node->word[i] = word[i];
    }
    new_node->word[len] = '\0';
    
    new_node->count = 1;
    new_node->next = ht->buckets[idx];
    ht->buckets[idx] = new_node;
    
    ht->unique_words++;
    return SUCCESS;
}

Status process_text(const char *text, HashTable *ht) {
    if (!text || !ht) {
        return ERR_INVALID;
    }
    
    size_t len = bounded_strlen(text, MAX_TEXT_LEN);
    char *buffer = malloc(len + 1);
    if (!buffer) {
        return ERR_MEMORY;
    }

    size_t buf_idx = 0;
    for (size_t i = 0; i <= len; i++) {
        if (i < len && isalpha((unsigned char)text[i])) {
            buffer[buf_idx++] = (char)tolower((unsigned char)text[i]);
        } else if (buf_idx > 0) {
            buffer[buf_idx] = '\0';
            Status status = insert_word_hash(ht, buffer);
            if (status != SUCCESS) {
                free(buffer);
                return status;
            }
            buf_idx = 0;
        }
    }
    
    free(buffer);
    return SUCCESS;
}

void flatten_hash_table(const HashTable *ht, WordFrequency *array) {
    if (!ht || !array) {
        return;
    }
    size_t index = 0;
    for (size_t i = 0; i < ht->size; i++) {
        HashNode *node = ht->buckets[i];
        while (node) {
            array[index].word = node->word;
            array[index].count = node->count;
            index++;
            node = node->next;
        }
    }
}

int compare_frequencies(const void *a, const void *b) {
    const WordFrequency *wf_a = (const WordFrequency *)a;
    const WordFrequency *wf_b = (const WordFrequency *)b;
    
    if (wf_a->count != wf_b->count) {
        return (wf_b->count > wf_a->count) - (wf_b->count < wf_a->count);
    }
    return strncmp(wf_a->word, wf_b->word, MAX_WORD_LEN);
}

void free_hash_table(HashTable *ht) {
    if (!ht || !ht->buckets) {
        return;
    }
    for (size_t i = 0; i < ht->size; i++) {
        HashNode *node = ht->buckets[i];
        while (node) {
            HashNode *next = node->next;
            free(node->word);
            free(node);
            node = next;
        }
    }
    free(ht->buckets);
    ht->buckets = NULL;
    ht->size = 0;
    ht->unique_words = 0;
}

void find_most_common_elements(const char *text, size_t top_n) {
    if (!text || top_n == 0) {
        return;
    }

    HashTable ht;
    if (init_hash_table(&ht, 4096) != SUCCESS) {
        return;
    }

    Status status = process_text(text, &ht);
    if (status != SUCCESS || ht.unique_words == 0) {
        free_hash_table(&ht);
        return;
    }

    WordFrequency *array = malloc(ht.unique_words * sizeof(WordFrequency));
    if (!array) {
        free_hash_table(&ht);
        return;
    }

    flatten_hash_table(&ht, array);
    qsort(array, ht.unique_words, sizeof(WordFrequency), compare_frequencies);

    size_t limit = (top_n < ht.unique_words) ? top_n : ht.unique_words;
    for (size_t i = 0; i < limit; i++) {
        printf("%s: %zu\n", array[i].word, array[i].count);
    }

    free(array);
    free_hash_table(&ht);
}

int main(void) {
    const char *text = "This is a test. This test is only a test! "
                       "Testing, testing, one, two, three. "
                       "If this had been a real emergency, "
                       "we would have more words. "
                       "Testing once more for the test.";
    
    find_most_common_elements(text, 5);
    
    return EXIT_SUCCESS;
}
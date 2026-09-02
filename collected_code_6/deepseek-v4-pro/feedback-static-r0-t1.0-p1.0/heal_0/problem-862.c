#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct WordCount {
    char *word;
    int count;
} WordCount;

typedef struct HashEntry {
    char *word;
    int count;
    struct HashEntry *next;
} HashEntry;

typedef struct HashMap {
    HashEntry **buckets;
    int size;
    int capacity;
} HashMap;

HashMap *hashmap_create(int capacity) {
    HashMap *map = malloc(sizeof(HashMap));
    if (!map) return NULL;
    map->capacity = capacity;
    map->size = 0;
    map->buckets = calloc(capacity, sizeof(HashEntry *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    return map;
}

unsigned int hash_function(const char *str, int capacity) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % capacity;
}

void hashmap_insert(HashMap *map, const char *word) {
    unsigned int index = hash_function(word, map->capacity);
    HashEntry *entry = map->buckets[index];
    while (entry) {
        if (strcmp(entry->word, word) == 0) {
            entry->count++;
            return;
        }
        entry = entry->next;
    }
    entry = malloc(sizeof(HashEntry));
    if (!entry) return;
    entry->word = malloc(strlen(word) + 1);
    if (!entry->word) {
        free(entry);
        return;
    }
    strcpy(entry->word, word);
    entry->count = 1;
    entry->next = map->buckets[index];
    map->buckets[index] = entry;
    map->size++;
}

void hashmap_free(HashMap *map) {
    if (!map) return;
    for (int i = 0; i < map->capacity; i++) {
        HashEntry *entry = map->buckets[i];
        while (entry) {
            HashEntry *next = entry->next;
            free(entry->word);
            free(entry);
            entry = next;
        }
    }
    free(map->buckets);
    free(map);
}

int compare_word_count(const void *a, const void *b) {
    const WordCount *wa = (const WordCount *)a;
    const WordCount *wb = (const WordCount *)b;
    if (wb->count != wa->count) {
        return wb->count - wa->count;
    }
    return strcmp(wa->word, wb->word);
}

WordCount *most_common_words(const char *text, int n, int *output_count) {
    if (!text || n <= 0) {
        *output_count = 0;
        return NULL;
    }

    HashMap *map = hashmap_create(1024);
    if (!map) {
        *output_count = 0;
        return NULL;
    }

    char buffer[256];
    int buffer_len = 0;
    const char *p = text;

    while (*p) {
        if (isalnum((unsigned char)*p)) {
            if (buffer_len < 255) {
                buffer[buffer_len++] = tolower((unsigned char)*p);
            }
        } else {
            if (buffer_len > 0) {
                buffer[buffer_len] = '\0';
                hashmap_insert(map, buffer);
                buffer_len = 0;
            }
        }
        p++;
    }
    if (buffer_len > 0) {
        buffer[buffer_len] = '\0';
        hashmap_insert(map, buffer);
    }

    if (map->size == 0) {
        hashmap_free(map);
        *output_count = 0;
        return NULL;
    }

    WordCount *pairs = malloc(map->size * sizeof(WordCount));
    if (!pairs) {
        hashmap_free(map);
        *output_count = 0;
        return NULL;
    }

    int idx = 0;
    for (int i = 0; i < map->capacity; i++) {
        HashEntry *entry = map->buckets[i];
        while (entry) {
            pairs[idx].word = entry->word;
            pairs[idx].count = entry->count;
            entry = entry->next;
            idx++;
        }
    }

    qsort(pairs, map->size, sizeof(WordCount), compare_word_count);

    int result_count = (n < map->size) ? n : map->size;
    WordCount *result = malloc(result_count * sizeof(WordCount));
    if (!result) {
        free(pairs);
        hashmap_free(map);
        *output_count = 0;
        return NULL;
    }

    for (int i = 0; i < result_count; i++) {
        result[i].word = malloc(strlen(pairs[i].word) + 1);
        if (!result[i].word) {
            for (int j = 0; j < i; j++) {
                free(result[j].word);
            }
            free(result);
            free(pairs);
            hashmap_free(map);
            *output_count = 0;
            return NULL;
        }
        strcpy(result[i].word, pairs[i].word);
        result[i].count = pairs[i].count;
    }

    free(pairs);
    hashmap_free(map);
    *output_count = result_count;
    return result;
}

void free_word_counts(WordCount *counts, int count) {
    if (!counts) return;
    for (int i = 0; i < count; i++) {
        free(counts[i].word);
    }
    free(counts);
}

int main(void) {
    const char *text = "The quick brown fox jumps over the lazy dog. The dog barks, and the fox runs away. Quick fox, lazy dog.";
    int count = 0;
    WordCount *results = most_common_words(text, 5, &count);

    if (results) {
        printf("Top %d most common words:\n", count);
        for (int i = 0; i < count; i++) {
            printf("%s: %d\n", results[i].word, results[i].count);
        }
        free_word_counts(results, count);
    } else {
        printf("No words found or error occurred.\n");
    }

    return 0;
}
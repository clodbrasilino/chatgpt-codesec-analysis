#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple key;
    int count;
    int occupied;
} MapEntry;

typedef struct {
    MapEntry *entries;
    int capacity;
} Map;

unsigned int hash_tuple(Tuple t, int capacity) {
    unsigned int hash = (t.a * 2654435761U) ^ (unsigned int)t.b;
    return hash % (unsigned int)capacity;
}

int map_init(Map *m, int capacity) {
    m->entries = calloc(capacity, sizeof(MapEntry));
    if (!m->entries) {
        return 0;
    }
    m->capacity = capacity;
    return 1;
}

void map_free(Map *m) {
    if (m->entries) {
        free(m->entries);
        m->entries = NULL;
        m->capacity = 0;
    }
}

int map_insert(Map *m, Tuple t) {
    if (!m->entries || m->capacity == 0) {
        return 0;
    }
    unsigned int idx = hash_tuple(t, m->capacity);
    for (int i = 0; i < m->capacity; i++) {
        int current = (idx + i) % m->capacity;
        if (!m->entries[current].occupied) {
            m->entries[current].key = t;
            m->entries[current].count = 1;
            m->entries[current].occupied = 1;
            return 1;
        } else if (m->entries[current].key.a == t.a && m->entries[current].key.b == t.b) {
            m->entries[current].count++;
            return 1;
        }
    }
    return 0;
}

typedef struct {
    int frequency;
    int record_count;
} FreqInfo;

void check_similar_occurrences(const Tuple *tuples, int num_tuples) {
    if (!tuples || num_tuples <= 0) {
        return;
    }

    int capacity = num_tuples * 2 + 1;
    Map m;
    if (!map_init(&m, capacity)) {
        return;
    }

    for (int i = 0; i < num_tuples; i++) {
        if (!map_insert(&m, tuples[i])) {
            map_free(&m);
            return;
        }
    }

    FreqInfo *freqs = malloc(num_tuples * sizeof(FreqInfo));
    if (!freqs) {
        map_free(&m);
        return;
    }
    int freq_count = 0;

    for (int i = 0; i < m.capacity; i++) {
        if (m.entries[i].occupied) {
            int current_freq = m.entries[i].count;
            int found = 0;
            for (int j = 0; j < freq_count; j++) {
                if (freqs[j].frequency == current_freq) {
                    freqs[j].record_count++;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                freqs[freq_count].frequency = current_freq;
                freqs[freq_count].record_count = 1;
                freq_count++;
            }
        }
    }

    for (int i = 0; i < freq_count; i++) {
        if (freqs[i].record_count > 1) {
            printf("%d records occur %d times each.\n", freqs[i].record_count, freqs[i].frequency);
        }
    }

    free(freqs);
    map_free(&m);
}

int main(void) {
    Tuple data[] = {
        {1, 2}, {3, 4}, {1, 2}, {5, 6},
        {3, 4}, {7, 8}, {1, 2}, {5, 6},
        {9, 10}, {7, 8}, {11, 12}
    };
    int n = sizeof(data) / sizeof(data[0]);
    check_similar_occurrences(data, n);
    return 0;
}
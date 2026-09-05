#include <stdio.h>
#include <stdlib.h>

typedef void* (*MapFunc)(void*);

typedef struct MapEntry {
    void* key;
    int count;
    struct MapEntry* next;
} MapEntry;

typedef struct Map {
    MapEntry** buckets;
    size_t size;
} Map;

Map* map_create(size_t size) {
    Map* m = (Map*)malloc(sizeof(Map));
    if (m == NULL) return NULL;
    m->buckets = (MapEntry**)calloc(size, sizeof(MapEntry*));
    if (m->buckets == NULL) {
        free(m);
        return NULL;
    }
    m->size = size;
    return m;
}

void map_insert_or_increment(Map* m, void* key) {
    if (m == NULL || key == NULL) return;
    size_t index = ((size_t)key) % m->size;
    MapEntry* entry = m->buckets[index];
    while (entry != NULL) {
        if (entry->key == key) {
            entry->count++;
            return;
        }
        entry = entry->next;
    }
    MapEntry* new_entry = (MapEntry*)malloc(sizeof(MapEntry));
    if (new_entry == NULL) return;
    new_entry->key = key;
    new_entry->count = 1;
    new_entry->next = m->buckets[index];
    m->buckets[index] = new_entry;
}

int map_get_count(Map* m, void* key) {
    if (m == NULL || key == NULL) return 0;
    size_t index = ((size_t)key) % m->size;
    MapEntry* entry = m->buckets[index];
    while (entry != NULL) {
        if (entry->key == key) {
            return entry->count;
        }
        entry = entry->next;
    }
    return 0;
}

void map_free(Map* m) {
    if (m == NULL) return;
    for (size_t i = 0; i < m->size; i++) {
        MapEntry* entry = m->buckets[i];
        while (entry != NULL) {
            MapEntry* next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(m->buckets);
    free(m);
}

int* map_int(void* item) {
    return (int*)item;
}

int count_same_pairs(void** list1, size_t size1, void** list2, size_t size2, MapFunc map) {
    if (list1 == NULL || list2 == NULL || map == NULL) return 0;
    size_t map_size = size1 > 0 ? size1 : 1;
    Map* m = map_create(map_size);
    if (m == NULL) return 0;

    for (size_t i = 0; i < size1; i++) {
        void* key = map(list1[i]);
        if (key != NULL) {
            map_insert_or_increment(m, key);
        }
    }

    int count = 0;
    for (size_t i = 0; i < size2; i++) {
        void* key = map(list2[i]);
        if (key != NULL) {
            int c = map_get_count(m, key);
            if (c > 0) {
                count++;
                map_insert_or_increment(m, key);
                MapEntry* e = m->buckets[((size_t)key) % m->size];
                while(e != NULL) {
                    if(e->key == key) {
                        e->count = c - 1;
                        break;
                    }
                    e = e->next;
                }
            }
        }
    }

    map_free(m);
    return count;
}

int main(void) {
    int val1 = 1, val2 = 2, val3 = 3, val4 = 1, val5 = 4;

    void* list1[] = { &val1, &val2, &val3, &val4 };
    size_t size1 = sizeof(list1) / sizeof(list1[0]);

    void* list2[] = { &val1, &val4, &val5 };
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    int result = count_same_pairs(list1, size1, list2, size2, map_int);
    printf("%d\n", result);

    return 0;
}
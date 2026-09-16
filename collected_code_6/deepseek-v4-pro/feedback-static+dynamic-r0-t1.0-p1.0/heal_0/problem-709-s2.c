#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry {
    int key;
    int value;
} Entry;

typedef struct ValueInfo {
    int value;
    int *keys;
    int key_count;
    int key_capacity;
} ValueInfo;

typedef struct UniqueCounter {
    ValueInfo *infos;
    int count;
    int capacity;
} UniqueCounter;

UniqueCounter *create_counter() {
    UniqueCounter *counter = malloc(sizeof(UniqueCounter));
    if (!counter) return NULL;
    counter->infos = malloc(sizeof(ValueInfo) * 8);
    if (!counter->infos) {
        free(counter);
        return NULL;
    }
    counter->count = 0;
    counter->capacity = 8;
    return counter;
}

static int contains_key(ValueInfo *info, int key) {
    for (int i = 0; i < info->key_count; i++) {
        if (info->keys[i] == key) return 1;
    }
    return 0;
}

static int add_key_to_info(ValueInfo *info, int key) {
    if (contains_key(info, key)) return 0;
    if (info->key_count >= info->key_capacity) {
        int new_capacity = info->key_capacity * 2;
        int *new_keys = realloc(info->keys, sizeof(int) * new_capacity);
        if (!new_keys) return 0;
        info->keys = new_keys;
        info->key_capacity = new_capacity;
    }
    info->keys[info->key_count++] = key;
    return 1;
}

static int find_or_create_info(UniqueCounter *counter, int value, ValueInfo **out_info) {
    for (int i = 0; i < counter->count; i++) {
        if (counter->infos[i].value == value) {
            *out_info = &counter->infos[i];
            return 1;
        }
    }
    if (counter->count >= counter->capacity) {
        int new_capacity = counter->capacity * 2;
        ValueInfo *new_infos = realloc(counter->infos, sizeof(ValueInfo) * new_capacity);
        if (!new_infos) return 0;
        counter->infos = new_infos;
        counter->capacity = new_capacity;
    }
    ValueInfo *info = &counter->infos[counter->count];
    info->value = value;
    info->keys = malloc(sizeof(int) * 4);
    if (!info->keys) return 0;
    info->key_count = 0;
    info->key_capacity = 4;
    counter->count++;
    *out_info = info;
    return 1;
}

void destroy_counter(UniqueCounter *counter) {
    if (!counter) return;
    for (int i = 0; i < counter->count; i++) {
        free(counter->infos[i].keys);
    }
    free(counter->infos);
    free(counter);
}

void count_unique_keys(Entry *entries, int entry_count, UniqueCounter **out_counter, int *out_success) {
    if (!entries || entry_count <= 0 || !out_counter || !out_success) {
        *out_success = 0;
        return;
    }
    
    UniqueCounter *counter = create_counter();
    if (!counter) {
        *out_success = 0;
        *out_counter = NULL;
        return;
    }
    
    for (int i = 0; i < entry_count; i++) {
        ValueInfo *info = NULL;
        if (!find_or_create_info(counter, entries[i].value, &info)) {
            destroy_counter(counter);
            *out_counter = NULL;
            *out_success = 0;
            return;
        }
        add_key_to_info(info, entries[i].key);
    }
    
    *out_counter = counter;
    *out_success = 1;
}

int main(void) {
    Entry entries[] = {
        {1, 100}, {2, 200}, {3, 100}, {4, 300},
        {5, 200}, {6, 100}, {7, 400}, {8, 300},
        {1, 100}, {2, 200}, {1, 100}, {9, 500}
    };
    int entry_count = sizeof(entries) / sizeof(entries[0]);
    
    UniqueCounter *counter = NULL;
    int success = 0;
    
    count_unique_keys(entries, entry_count, &counter, &success);
    
    if (!success || !counter) {
        printf("Failed to count unique keys\n");
        return 1;
    }
    
    printf("Value | Unique Key Count\n");
    printf("--------------------\n");
    for (int i = 0; i < counter->count; i++) {
        ValueInfo *info = &counter->infos[i];
        printf("%5d | %5d\n", info->value, info->key_count);
    }
    
    destroy_counter(counter);
    
    return 0;
}
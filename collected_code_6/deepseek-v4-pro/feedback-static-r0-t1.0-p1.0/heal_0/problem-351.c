#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 16
#define LOAD_FACTOR 0.75

typedef struct Entry {
    int key;
    int count;
    struct Entry *next;
} Entry;

typedef struct {
    Entry **buckets;
    int capacity;
    int size;
} HashMap;

static unsigned int hash_int(int key, int capacity) {
    unsigned int k = (unsigned int)key;
    k ^= k >> 16;
    k *= 0x85ebca6b;
    k ^= k >> 13;
    k *= 0xc2b2ae35;
    k ^= k >> 16;
    return k % (unsigned int)capacity;
}

static HashMap *hashmap_create(void) {
    HashMap *map = (HashMap *)malloc(sizeof(HashMap));
    if (!map) return NULL;
    map->capacity = INITIAL_CAPACITY;
    map->size = 0;
    map->buckets = (Entry **)calloc((size_t)map->capacity, sizeof(Entry *));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    return map;
}

static void hashmap_destroy(HashMap *map) {
    if (!map) return;
    for (int i = 0; i < map->capacity; i++) {
        Entry *entry = map->buckets[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry);
            entry = next;
        }
    }
    free(map->buckets);
    free(map);
}

static int hashmap_resize(HashMap *map) {
    int new_capacity = map->capacity * 2;
    Entry **new_buckets = (Entry **)calloc((size_t)new_capacity, sizeof(Entry *));
    if (!new_buckets) return 0;

    for (int i = 0; i < map->capacity; i++) {
        Entry *entry = map->buckets[i];
        while (entry) {
            Entry *next = entry->next;
            unsigned int idx = hash_int(entry->key, new_capacity);
            entry->next = new_buckets[idx];
            new_buckets[idx] = entry;
            entry = next;
        }
    }

    free(map->buckets);
    map->buckets = new_buckets;
    map->capacity = new_capacity;
    return 1;
}

static int hashmap_increment(HashMap *map, int key) {
    if ((float)map->size / (float)map->capacity > LOAD_FACTOR) {
        if (!hashmap_resize(map)) return -1;
    }

    unsigned int idx = hash_int(key, map->capacity);
    Entry *entry = map->buckets[idx];

    while (entry) {
        if (entry->key == key) {
            entry->count++;
            return entry->count;
        }
        entry = entry->next;
    }

    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    if (!new_entry) return -1;
    new_entry->key = key;
    new_entry->count = 1;
    new_entry->next = map->buckets[idx];
    map->buckets[idx] = new_entry;
    map->size++;
    return 1;
}

int first_element_k_times(const int *arr, int n, int k) {
    if (!arr || n <= 0 || k <= 0) {
        return -1;
    }

    HashMap *map = hashmap_create();
    if (!map) return -1;

    int *first_index = (int *)malloc((size_t)n * sizeof(int));
    if (!first_index) {
        hashmap_destroy(map);
        return -1;
    }
    for (int i = 0; i < n; i++) {
        first_index[i] = -1;
    }

    int distinct_count = 0;
    int *distinct_keys = (int *)malloc((size_t)n * sizeof(int));
    if (!distinct_keys) {
        free(first_index);
        hashmap_destroy(map);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        int count = hashmap_increment(map, arr[i]);
        if (count < 0) {
            free(distinct_keys);
            free(first_index);
            hashmap_destroy(map);
            return -1;
        }

        int key_index = -1;
        for (int j = 0; j < distinct_count; j++) {
            if (distinct_keys[j] == arr[i]) {
                key_index = j;
                break;
            }
        }

        if (key_index == -1) {
            key_index = distinct_count;
            distinct_keys[key_index] = arr[i];
            distinct_count++;
        }

        if (first_index[key_index] == -1) {
            first_index[key_index] = i;
        }

        if (count == k) {
            int result = arr[first_index[key_index]];
            free(distinct_keys);
            free(first_index);
            hashmap_destroy(map);
            return result;
        }
    }

    free(distinct_keys);
    free(first_index);
    hashmap_destroy(map);
    return -1;
}

int main(void) {
    int arr1[] = {1, 7, 4, 3, 4, 8, 7};
    int n1 = sizeof(arr1) / sizeof(arr1[0]);
    int k1 = 2;
    int result1 = first_element_k_times(arr1, n1, k1);
    printf("First element occurring %d times in arr1: %d\n", k1, result1);

    int arr2[] = {3, 1, 3, 1, 3};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    int k2 = 3;
    int result2 = first_element_k_times(arr2, n2, k2);
    printf("First element occurring %d times in arr2: %d\n", k2, result2);

    int arr3[] = {1, 2, 3, 4};
    int n3 = sizeof(arr3) / sizeof(arr3[0]);
    int k3 = 2;
    int result3 = first_element_k_times(arr3, n3, k3);
    printf("First element occurring %d times in arr3: %d\n", k3, result3);

    int arr4[] = {5, 5, 5, 5};
    int n4 = sizeof(arr4) / sizeof(arr4[0]);
    int k4 = 4;
    int result4 = first_element_k_times(arr4, n4, k4);
    printf("First element occurring %d times in arr4: %d\n", k4, result4);

    int arr5[] = {10, 20, 30, 20, 10, 40};
    int n5 = sizeof(arr5) / sizeof(arr5[0]);
    int k5 = 2;
    int result5 = first_element_k_times(arr5, n5, k5);
    printf("First element occurring %d times in arr5: %d\n", k5, result5);

    return 0;
}
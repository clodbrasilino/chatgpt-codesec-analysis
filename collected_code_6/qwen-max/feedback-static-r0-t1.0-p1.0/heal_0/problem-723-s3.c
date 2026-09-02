#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int count;
} PairCount;

unsigned long hash_function(int key, unsigned long table_size) {
    return (key % table_size);
}

PairCount *create_pair_count(int key) {
    PairCount *pc = (PairCount *)malloc(sizeof(PairCount));
    pc->key = key;
    pc->count = 0;
    return pc;
}

void insert_into_map(PairCount **map, int key, unsigned long table_size) {
    unsigned long index = hash_function(key, table_size);
    if (map[index] == NULL) {
        map[index] = create_pair_count(key);
    }
    map[index]->count++;
}

int find_in_map(PairCount **map, int key, unsigned long table_size) {
    unsigned long index = hash_function(key, table_size);
    if (map[index] != NULL && map[index]->key == key) {
        return map[index]->count;
    }
    return 0;
}

int count_same_pairs(int *list1, int list1Size, int *list2, int list2Size) {
    PairCount **map = (PairCount **)calloc(1000, sizeof(PairCount *));
    for (int i = 0; i < list1Size; i++) {
        insert_into_map(map, list1[i], 1000);
    }
    int count = 0;
    for (int i = 0; i < list2Size; i++) {
        count += find_in_map(map, list2[i], 1000);
    }
    for (int i = 0; i < 1000; i++) {
        if (map[i] != NULL) {
            free(map[i]);
        }
    }
    free(map);
    return count;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {3, 4, 5, 6, 7};
    int list1Size = sizeof(list1) / sizeof(list1[0]);
    int list2Size = sizeof(list2) / sizeof(list2[0]);

    int pairs = count_same_pairs(list1, list1Size, list2, list2Size);
    printf("Number of same pairs: %d\n", pairs);

    return 0;
}
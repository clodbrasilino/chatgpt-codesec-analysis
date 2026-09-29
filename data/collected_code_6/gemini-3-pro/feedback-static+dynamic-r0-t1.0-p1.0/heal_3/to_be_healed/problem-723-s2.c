#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair *items;
    size_t size;
    size_t capacity;
} Map;

Map* create_map(size_t capacity) {
    Map *map = (Map*)malloc(sizeof(Map));
    if (!map) {
        return NULL;
    }
    map->items = (KeyValuePair*)malloc(capacity * sizeof(KeyValuePair));
    if (!map->items) {
        free(map);
        return NULL;
    }
    map->size = 0;
    map->capacity = capacity;
    return map;
}

void free_map(Map *map) {
    if (map) {
        free(map->items);
        free(map);
    }
}

void put(Map *map, int key) {
    if (!map) return;
    for (size_t i = 0; i < map->size; i++) {
        if (map->items[i].key == key) {
            map->items[i].value++;
            return;
        }
    }
    if (map->size < map->capacity) {
        map->items[map->size].key = key;
        map->items[map->size].value = 1;
        map->size++;
    }
}

int get_and_decrement(Map *map, int key) {
    if (!map) return 0;
    for (size_t i = 0; i < map->size; i++) {
        if (map->items[i].key == key) {
            if (map->items[i].value > 0) {
                map->items[i].value--;
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 4, got 3
  *  test case 1 failed: expected 11, got 8
  *  test case 2 failed: expected 1, got 3
  */

int count_same_pairs(const int *list1, size_t size1, const int *list2, size_t size2) {
    if (!list1 || !list2 || size1 == 0 || size2 == 0) {
        return 0;
    }

    Map *map1 = create_map(size1);
    if (!map1) return 0;

    for (size_t i = 0; i < size1; i++) {
        put(map1, list1[i]);
    }

    int same_pairs_count = 0;
    for (size_t i = 0; i < size2; i++) {
        same_pairs_count += get_and_decrement(map1, list2[i]);
    }

    free_map(map1);
    return same_pairs_count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 5, 2};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);

    int list2[] = {2, 5, 6, 2, 7};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);

    int count = count_same_pairs(list1, size1, list2, size2);
    
    printf("%d\n", count);

    return 0;
}
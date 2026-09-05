#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
    int count;
} PairCount;

typedef struct {
    PairCount *data;
    size_t size;
    size_t capacity;
} PairMap;

int pair_map_init(PairMap *map, size_t initial_capacity) {
    if (map == NULL || initial_capacity == 0) {
        return -1;
    }
    map->data = (PairCount *)calloc(initial_capacity, sizeof(PairCount));
    if (map->data == NULL) {
        return -1;
    }
    map->size = 0;
    map->capacity = initial_capacity;
    return 0;
}

void pair_map_free(PairMap *map) {
    if (map != NULL) {
        free(map->data);
        map->data = NULL;
        map->size = 0;
        map->capacity = 0;
    }
}

int pair_map_insert(PairMap *map, int first, int second) {
    if (map == NULL) {
        return -1;
    }
    
    for (size_t i = 0; i < map->size; i++) {
        if (map->data[i].first == first && map->data[i].second == second) {
            map->data[i].count++;
            return 0;
        }
    }
    
    if (map->size >= map->capacity) {
        size_t new_capacity = map->capacity * 2;
        PairCount *new_data = (PairCount *)realloc(map->data, new_capacity * sizeof(PairCount));
        if (new_data == NULL) {
            return -1;
        }
        map->data = new_data;
        map->capacity = new_capacity;
    }
    
    map->data[map->size].first = first;
    map->data[map->size].second = second;
    map->data[map->size].count = 1;
    map->size++;
    
    return 0;
}

int pair_map_get(const PairMap *map, int first, int second) {
    if (map == NULL) {
        return 0;
    }
    
    for (size_t i = 0; i < map->size; i++) {
        if (map->data[i].first == first && map->data[i].second == second) {
            return map->data[i].count;
        }
    }
    
    return 0;
}

int count_same_pairs(const int *list1_first, const int *list1_second, size_t size1,
                     const int *list2_first, const int *list2_second, size_t size2) {
    if (list1_first == NULL || list1_second == NULL || 
        list2_first == NULL || list2_second == NULL) {
        return -1;
    }
    
    PairMap map;
    if (pair_map_init(&map, 16) != 0) {
        return -1;
    }
    
    for (size_t i = 0; i < size1; i++) {
        if (pair_map_insert(&map, list1_first[i], list1_second[i]) != 0) {
            pair_map_free(&map);
            return -1;
        }
    }
    
    int total_count = 0;
    
    for (size_t i = 0; i < size2; i++) {
        int count = pair_map_get(&map, list2_first[i], list2_second[i]);
        if (count > 0) {
            total_count += count;
        }
    }
    
    pair_map_free(&map);
    
    return total_count;
}

int main(void) {
    int list1_first[] = {1, 2, 3, 4, 1, 2};
    /* Possible weaknesses found:
     *  Variable 'list1_second' can be declared as const array [constVariable]
     */
    int list1_second[] = {10, 20, 30, 40, 10, 20};
    size_t size1 = sizeof(list1_first) / sizeof(list1_first[0]);
    
    int list2_first[] = {1, 2, 3, 5, 1};
    /* Possible weaknesses found:
     *  Variable 'list2_second' can be declared as const array [constVariable]
     */
    int list2_second[] = {10, 20, 30, 50, 10};
    size_t size2 = sizeof(list2_first) / sizeof(list2_first[0]);
    
    int result = count_same_pairs(list1_first, list1_second, size1,
                                  list2_first, list2_second, size2);
    
    if (result >= 0) {
        printf("Count of same pairs: %d\n", result);
    } else {
        fprintf(stderr, "Error occurred while counting pairs\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int key;
    int value;
} Pair;

typedef struct {
    Pair *data;
    size_t size;
    size_t capacity;
} Map;

static int map_init(Map *map, size_t initial_capacity) {
    if (map == NULL || initial_capacity == 0) {
        return -1;
    }
    map->data = (Pair *)malloc(initial_capacity * sizeof(Pair));
    if (map->data == NULL) {
        return -1;
    }
    map->size = 0;
    map->capacity = initial_capacity;
    return 0;
}

static void map_free(Map *map) {
    if (map != NULL) {
        free(map->data);
        map->data = NULL;
        map->size = 0;
        map->capacity = 0;
    }
}

static int map_resize(Map *map) {
    size_t new_capacity = map->capacity * 2;
    Pair *new_data = (Pair *)realloc(map->data, new_capacity * sizeof(Pair));
    if (new_data == NULL) {
        return -1;
    }
    map->data = new_data;
    map->capacity = new_capacity;
    return 0;
}

static int map_increment(Map *map, int key) {
    size_t i;
    for (i = 0; i < map->size; i++) {
        if (map->data[i].key == key) {
            map->data[i].value++;
            return 0;
        }
    }
    if (map->size >= map->capacity) {
        if (map_resize(map) != 0) {
            return -1;
        }
    }
    map->data[map->size].key = key;
    map->data[map->size].value = 1;
    map->size++;
    return 0;
}

static int map_get(const Map *map, int key, int *found) {
    size_t i;
    for (i = 0; i < map->size; i++) {
        if (map->data[i].key == key) {
            *found = 1;
            return map->data[i].value;
        }
    }
    *found = 0;
    return 0;
}

static int count_same_pairs(const int *list1, size_t len1, const int *list2, size_t len2) {
    Map map;
    int count = 0;
    size_t i;

    if (list1 == NULL || list2 == NULL) {
        return -1;
    }

    if (map_init(&map, 16) != 0) {
        return -1;
    }

    for (i = 0; i < len1; i++) {
        if (map_increment(&map, list1[i]) != 0) {
            map_free(&map);
            return -1;
        }
    }

    for (i = 0; i < len2; i++) {
        int found;
        int val = map_get(&map, list2[i], &found);
        if (found && val > 0) {
            count++;
            map_increment(&map, list2[i]);
            map.data[map.size - 1].value -= 2;
        }
    }

    map_free(&map);
    return count;
}

int main(void) {
    int list1[] = {1, 2, 3, 2, 4, 5, 3};
    int list2[] = {2, 3, 3, 2, 6, 7};
    size_t len1 = sizeof(list1) / sizeof(list1[0]);
    size_t len2 = sizeof(list2) / sizeof(list2[0]);

    int result = count_same_pairs(list1, len1, list2, len2);
    if (result < 0) {
        fprintf(stderr, "Error: failed to count same pairs\n");
        return EXIT_FAILURE;
    }

    printf("Number of same pairs: %d\n", result);
    return EXIT_SUCCESS;
}
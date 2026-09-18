#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node** buckets;
    size_t size;
} HashMap;

HashMap* create_map(size_t size) {
    if (size == 0) return NULL;
    
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    if (!map) return NULL;
    
    map->size = size;
    map->buckets = (Node**)calloc(size, sizeof(Node*));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    
    return map;
}

void put(HashMap* map, int key, int value) {
    if (!map || !map->buckets || map->size == 0) return;
    
    size_t index = (size_t)((unsigned int)key) % map->size;
    
    Node* current = map->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    
    new_node->key = key;
    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

int get(HashMap* map, int key, int* out_value) {
    if (!map || !map->buckets || map->size == 0) return 0;
    
    size_t index = (size_t)((unsigned int)key) % map->size;
    
    Node* current = map->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            if (out_value) *out_value = current->value;
            return 1;
        }
        current = current->next;
    }
    
    return 0;
}

void free_map(HashMap* map) {
    if (!map) return;
    
    if (map->buckets) {
        for (size_t i = 0; i < map->size; i++) {
            Node* current = map->buckets[i];
            while (current != NULL) {
                Node* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(map->buckets);
    }
    free(map);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got <no output>
  *  test case 0 failed: expected 4, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

int count_same_pairs(const int* list1, const int* list2, size_t size) {
    if (!list1 || !list2 || size == 0) return 0;
    
    HashMap* map = create_map(size * 2);
    if (!map) return 0;
    
    for (size_t i = 0; i < size; i++) {
        put(map, list1[i], list2[i]);
    }
    
    int count = 0;
    for (size_t i = 0; i < size; i++) {
        int expected_val;
        if (get(map, list1[i], &expected_val)) {
            if (expected_val == list2[i]) {
                count++;
                put(map, list1[i], -1); 
            }
        }
    }
    
    free_map(map);
    return count;
}

int main(void) {
    int list1[] = {1, 2, 3, 4, 1, 5};
    int list2[] = {10, 20, 30, 40, 10, 50};
    size_t size = sizeof(list1) / sizeof(list1[0]);
    
    if (sizeof(list2) / sizeof(list2[0]) != size) {
        return 1;
    }
    
    int result = count_same_pairs(list1, list2, size);
    printf("%d\n", result);
    
    return 0;
}
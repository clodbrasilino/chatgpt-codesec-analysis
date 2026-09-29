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
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return;
    
    new_node->key = key;
    new_node->value = value;
    new_node->next = map->buckets[index];
    map->buckets[index] = new_node;
}

int get_and_remove(HashMap* map, int key, int value) {
    if (!map || !map->buckets || map->size == 0) return 0;
    
    size_t index = (size_t)((unsigned int)key) % map->size;
    
    Node* current = map->buckets[index];
    Node* prev = NULL;
    
    while (current != NULL) {
        if (current->key == key && current->value == value) {
            if (prev) {
                prev->next = current->next;
            } else {
                map->buckets[index] = current->next;
            }
            free(current);
            return 1;
        }
        prev = current;
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
  *  test case 2 failed: expected 1, got <no output>
  *  test case 0 failed: expected 4, got <no output>
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
        if (get_and_remove(map, list2[i], list1[i])) {
            count++;
        }
    }
    
    free_map(map);
    return count;
}

int main(void) {
    int size_in;
    if (scanf("%d", &size_in) != 1) {
        return 0;
    }
    
    if (size_in <= 0) {
        printf("0\n");
        return 0;
    }
    
    size_t size = (size_t)size_in;

    int* list1 = (int*)malloc(size * sizeof(int));
    int* list2 = (int*)malloc(size * sizeof(int));
    
    if (!list1 || !list2) {
        free(list1);
        free(list2);
        return 1;
    }
    
    size_t actual_size1 = 0;
    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &list1[i]) == 1) {
            actual_size1++;
        } else {
            break;
        }
    }
    
    size_t actual_size2 = 0;
    for (size_t i = 0; i < size; i++) {
        if (scanf("%d", &list2[i]) == 1) {
            actual_size2++;
        } else {
            break;
        }
    }
    
    size_t min_size = actual_size1 < actual_size2 ? actual_size1 : actual_size2;
    
    int result = count_same_pairs(list1, list2, min_size);
    printf("%d\n", result);
    
    free(list1);
    free(list2);
    
    return 0;
}
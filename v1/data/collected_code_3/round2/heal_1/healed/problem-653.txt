#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct {
    char *key;
    Node *values;
} Map;

Map *createMap(char *key, char *value) {
    Map *map = (Map *)malloc(sizeof(Map));
    if(map == NULL){
        return NULL;
    }
    map->key = strdup(key);
    map->values = (Node *)malloc(sizeof(Node));
    if(map->values == NULL){
        free(map);
        return NULL;
    }
    map->values->value = strdup(value);
    map->values->next = NULL;
    return map;
}

void addValue(Map *map, char *value) {
    Node *current = map->values;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (Node *)malloc(sizeof(Node));
    if(current->next == NULL){
        return;
    }
    current->next->value = strdup(value);
    current->next->next = NULL;
}

void printMap(Map *map) {
    printf("%s: ", map->key);
    Node *current = map->values;
    while (current != NULL) {
        printf("%s ", current->value);
        current = current->next;
    }
    printf("\n");
}

void freeMap(Map *map) {
    free(map->key);
    Node *current = map->values;
    Node *next;
    while (current != NULL) {
        next = current->next;
        free(current->value);
        free(current);
        current = next;
    }
    free(map);
}

int main() {
    Map *map = createMap("key1", "value1");
    if(map == NULL){
        return 1;
    }
    addValue(map, "value2");
    addValue(map, "value3");
    printMap(map);
    freeMap(map);
    return 0;
}
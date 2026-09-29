#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct Map {
    char *key; 
    Node *nodes;
    struct Map *next;
} Map;

Map* new_map(){
    Map *newMap;
    if ((newMap = malloc(sizeof(Map))) == NULL)
        return NULL;
    newMap->key = NULL;
    newMap->nodes = NULL;
    newMap->next = NULL;
    return newMap;
}

Node* node_create(char *value) {
    Node *node;
    if((node = malloc(sizeof(Node))) == NULL)
        return NULL;
    if((node->value = malloc(strlen(value) + 1)) == NULL)
        return NULL;
    strcpy(node->value, value);
    node->next = NULL;
    return node;
}

void insert_pair(Map **map, char *key, char *value) {
    if (map == NULL || key == NULL || value == NULL)
        return;

    if (*map == NULL) {
        if ((*map = new_map()) == NULL)
            return;
        if (((*map)->key = malloc(strlen(key) + 1)) == NULL)
            return;
        strcpy((*map)->key, key);
        if (((*map)->nodes = node_create(value)) == NULL)
            return;
    } else if ((*map)->key != NULL && strcmp((*map)->key, key) == 0) {
        Node *node;
        if ((node = node_create(value)) == NULL)
            return;
        node->next = (*map)->nodes;
        (*map)->nodes = node;
    } else {
        insert_pair(&((*map)->next), key, value);
    }
}

void print_map(Map *map) {
    if (map != NULL) {
        printf("Key: %s\n", map->key);
        Node* node = map->nodes;

        while (node != NULL) {
            printf("Value: %s\n", node->value);
            node = node->next;
        }
        print_map(map->next);
    }
}

void free_node(Node *node){
    if(node != NULL) {
        free_node(node->next);
        free(node->value);
        free(node);
    }
}

void free_map(Map *map) {
    if(map != NULL) {
        free_map(map->next);
        free_node(map->nodes);
        free(map->key);
        free(map);
    }
}

int main() {
    Map *map = NULL;

    insert_pair(&map, "fruits", "apple");
    insert_pair(&map, "fruits", "banana");
    insert_pair(&map, "fruits", "cherry");
    insert_pair(&map, "vegetables", "carrot");

    print_map(map);

    free_map(map);

    return 0;
}
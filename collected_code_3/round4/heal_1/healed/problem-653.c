#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *value;
    struct Node *next;
} Node;

typedef struct Map {
    char *key;
    Node *values;
    struct Map *next;
} Map;

Node* createNode(char *value) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

Map* createMap(char *key, char *value) {
    Map *newMap = (Map*) malloc(sizeof(Map));
    if (newMap == NULL) {
        return NULL;
    }
    newMap->key = key;
    newMap->values = createNode(value);
    if (newMap->values == NULL) {
        free(newMap);
        return NULL;
    }
    newMap->next = NULL;
    return newMap;
}

void addValue(Map *map, char *key, char *value) {
    while(map != NULL) {
        if(strcmp(map->key, key) == 0) {
            Node *temp = map->values;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = createNode(value);
            if (temp->next == NULL) {
                return;
            }
            return;
        }
        map = map->next;
    }
}

void printMap(Map *map) {
    while(map != NULL) {
        printf("%s: ", map->key);
        Node *temp = map->values;
        while(temp != NULL) {
            printf("%s ", temp->value);
            temp = temp->next;
        }
        printf("\n");
        map = map->next;
    }
}

int main() {
    Map *map = createMap("key1", "value1");
    if (map == NULL) {
        return -1;
    }
    map->next = createMap("key2", "value2");
    if (map->next == NULL) {
        return -1;
    }
    addValue(map, "key1", "value3");
    addValue(map, "key2", "value4");
    printMap(map);
    return 0;
}
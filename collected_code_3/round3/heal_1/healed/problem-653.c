#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* value;
    struct Node* next;
} Node;

typedef struct Map {
    char* key;
    Node* values;
    struct Map* next;
} Map;

Node* createNode(char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

Map* createMap(char* key, char* value) {
    Map* newMap = (Map*)malloc(sizeof(Map));
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

void addValue(Map* map, char* key, char* value) {
    while(map != NULL) {
        if(strcmp(map->key, key) == 0) {
            Node* temp = map->values;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            Node* newNode = createNode(value);
            if (newNode == NULL) {
                return;
            }
            temp->next = newNode;
            return;
        }
        map = map->next;
    }
}

Map* addKey(Map* map, char* key, char* value) {
    if(map == NULL) {
        return createMap(key, value);
    }

    Map* temp = map;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    Map* newMap = createMap(key, value);
    if (newMap == NULL) {
        return map;
    }
    temp->next = newMap;
    return map;
}

void printMap(Map* map) {
    while(map != NULL) {
        printf("%s: ", map->key);
        Node* temp = map->values;
        while(temp != NULL) {
            printf("%s ", temp->value);
            temp = temp->next;
        }
        printf("\n");
        map = map->next;
    }
}

int main() {
    Map* map = NULL;
    map = addKey(map, "key1", "value1");
    if (map == NULL) {
        return 1;
    }
    addValue(map, "key1", "value2");
    map = addKey(map, "key2", "value3");
    if (map == NULL) {
        return 1;
    }
    printMap(map);
    return 0;
}
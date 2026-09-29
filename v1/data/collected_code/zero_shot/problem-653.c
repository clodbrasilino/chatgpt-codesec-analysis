#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 100
#define MAX_VALUE_LENGTH 100

typedef struct KeyValue {
    char key[MAX_KEY_LENGTH];
    char value[MAX_VALUE_LENGTH];
} KeyValue;

typedef struct Node {
    struct Node* next;
    KeyValue data;
} Node;

typedef struct List {
    Node* head;
    int size;
} List;

typedef struct Map {
    List* lists;
    int capacity;
    int size;
} Map;

Map* createMap(int capacity) {
    Map* map = (Map*)malloc(sizeof(Map));
    map->lists = (List*)malloc(capacity * sizeof(List));
    map->capacity = capacity;
    map->size = 0;
    
    for (int i = 0; i < capacity; i++) {
        map->lists[i].head = NULL;
        map->lists[i].size = 0;
    }
    
    return map;
}

unsigned long hash(char* key) {
    unsigned long hash = 5381;
    int c;
    
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
}

void insert(Map* map, char* key, char* value) {
    unsigned long index = hash(key) % map->capacity;
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->data.key, key);
    strcpy(newNode->data.value, value);
    newNode->next = NULL;
    
    if (map->lists[index].head == NULL) {
        map->lists[index].head = newNode;
    } else {
        Node* current = map->lists[index].head;
        while (current->next != NULL) {
            current = current->next;
        }
        
        current->next = newNode;
    }
    
    map->lists[index].size++;
    map->size++;
}

List* getList(Map* map, char* key) {
    unsigned long index = hash(key) % map->capacity;
    
    return &(map->lists[index]);
}

void printMap(Map* map) {
    for (int i = 0; i < map->capacity; i++) {
        List* list = &(map->lists[i]);
        Node* current = list->head;
        
        while (current != NULL) {
            printf("Key: %s, Value: %s\n", current->data.key, current->data.value);
            current = current->next;
        }
    }
}

int main() {
    Map* map = createMap(10);
    
    insert(map, "fruit", "apple");
    insert(map, "fruit", "banana");
    insert(map, "color", "red");
    insert(map, "color", "blue");
    
    List* fruitList = getList(map, "fruit");
    printf("Fruit List: ");
    Node* current = fruitList->head;
    while (current != NULL) {
        printf("%s ", current->data.value);
        current = current->next;
    }
    
    List* colorList = getList(map, "color");
    printf("\nColor List: ");
    current = colorList->head;
    while (current != NULL) {
        printf("%s ", current->data.value);
        current = current->next;
    }
    
    free(map->lists);
    free(map);
    
    return 0;
}
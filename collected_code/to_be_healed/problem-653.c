#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 100
#define MAX_VALUE_LENGTH 100

typedef struct KeyValue {
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
    char key[MAX_KEY_LENGTH];
    /* Possible weaknesses found:
     *   Statically-sized arrays can be improperly restricted, leading to potential  overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use  functions that limit length, or ensure that the size is larger than the  maximum possible length.
     */
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
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'map' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    map->lists = (List*)malloc(capacity * sizeof(List));
    map->capacity = capacity;
    map->size = 0;
    
    for (int i = 0; i < capacity; i++) {
        /* Possible weaknesses found:
         *  dereference of possibly-NULL '*map.lists + (long unsigned int)i * 16' [CWE-690] [-Wanalyzer-possible-null-dereference]
         */
        map->lists[i].head = NULL;
        map->lists[i].size = 0;
    }
    
    return map;
}

unsigned long hash(char* key) {
    unsigned long hash = 5381;
    int c;
    
    /* Possible weaknesses found:
     *  Cannot determine that '*key++' is initialized [premium-bughuntingUninit]
     */
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash;
}

void insert(Map* map, char* key, char* value) {
    unsigned long index = hash(key) % map->capacity;
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    /* Possible weaknesses found:
     *  Cannot determine that 'key[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(newNode->data.key, key);
    /* Possible weaknesses found:
     *  Cannot determine that 'value[0]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
     *   Does not check for buffer overflows when copying to destination [MS-banned]  (CWE-120). Consider using snprintf, strcpy_s, or strlcpy (warning: strncpy  easily misused).
     */
    strcpy(newNode->data.value, value);
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char** items;
    int size;
    int max;
} StringList;

StringList* createList(int size) {
    StringList* list = malloc(sizeof(StringList));

    if (!list)
        exit(1);

    list->items = malloc(size * sizeof(char*));

    if (!list->items) {
        free(list);
        return NULL;
    }
    
    list->size = 0;
    list->max = size;
    return list;
}

void prependString(StringList* list, char* str) {
    if (!list || !str) {
        printf("Failed to prepend\n");
        exit(1);
    }

    for (int i = 0; i < list->size; i++) {
        char temp[MAX_SIZE];
        strncpy(temp, str, MAX_SIZE);
        strncat(temp, list->items[i], MAX_SIZE - strlen(temp) - 1);
        char* newStr = malloc((strlen(temp) + 1) * sizeof(char));

        if (!newStr) {
            printf("Memory allocation failed!\n");
            exit(1);    
        }
        
        strncpy(newStr, temp, strlen(temp) + 1);
        free(list->items[i]);
        list->items[i] = newStr;
    }
}

void addString(StringList* list, char* str) {
    if (!list || !str || list->size >= list->max) exit(1);

    char *strCopy = malloc((strlen(str) + 1) * sizeof(char));

    if (!strCopy) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    strncpy(strCopy, str, strlen(str) + 1);
    list->items[list->size++] = strCopy;
}

void printList(StringList* list) {
    if (!list) exit(1);

    for (int i = 0; i < list->size; i++) {
        printf("%s\n", list->items[i]);
    }
}

void freeList(StringList* list) {
    if (!list) return;

    for (int i = 0; i < list->size; i++) {
        free(list->items[i]);
    }

    free(list->items);
    free(list);
}

int main() {
    StringList* list = createList(4);

    if (!list) {
        printf("Failed to create list!\n");
        exit(1);
    }

    addString(list, "Hello");
    addString(list, "World");
    addString(list, "!");

    prependString(list, "Prefix: ");
    printList(list);

    freeList(list);

    return 0;
}
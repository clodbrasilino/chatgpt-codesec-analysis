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
    StringList* list = (StringList*) calloc(1, sizeof(StringList));
    if (!list) exit(1);
    list->items = (char**) calloc(size, sizeof(char*));
    if (!list->items) {
        free(list);
        list = NULL;
    } else {
        list->size = 0;
    }
    /* Possible weaknesses found:
     *  dereference of NULL 'list' [CWE-476] [-Wanalyzer-null-dereference]
     */
    list->max = size;
    return list;
}

void prependString(StringList* list, char* str) {
    if (!list || !str) {
        printf("Failed to prepend!\n");
        exit(1);
    }

    for (int i = 0; i < list->size; i++) {
        char temp[MAX_SIZE];
        strcpy(temp, str);
        strcat(temp, list->items[i]);
        char* newStr = (char*)calloc((strlen(temp) + 1), sizeof(char));
        if (!newStr) {
            printf("Memory allocation failed!\n");
            exit(1);    
        }
 
        strcpy(newStr, temp);
        free(list->items[i]);
        list->items[i] = newStr;
    }
/* Possible weaknesses found:
 *  leak of 'newStr' [CWE-401] [-Wanalyzer-malloc-leak]
 */
}

void addString(StringList* list, char* str) {
    if (!list || !str || list->size >= list->max) exit(1);

    char *strCopy = (char *) calloc((strlen(str) + 1), sizeof(char));
    if (!strCopy) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    strcpy(strCopy, str);
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

    addString(list, "Hello");
    addString(list, "World");
    addString(list, "!");

    prependString(list, "Prefix: ");
    printList(list);

    freeList(list);

    return 0;
}
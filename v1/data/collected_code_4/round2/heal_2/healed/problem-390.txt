#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char** items;
    int size;
} StringList;

StringList* createList(int size) {
    StringList* list = (StringList*) calloc(1, sizeof(StringList));

    if (list != NULL) {
            list->items = (char**) calloc(size, sizeof(char*));
        if (list->items == NULL) {
            free(list);
            list = NULL;
        } else {
            list->size = 0;
        }
    }

    return list;
}

void prependString(StringList* list, char* str) {
    if (list != NULL && str != NULL) {
        for (int i = 0; i < list->size; i++) {
            char temp[MAX_SIZE];
            strcpy(temp, str);
            strcat(temp, list->items[i]);

            char* newStr = (char*)calloc((strlen(temp) + 1), sizeof(char));

            if (newStr != NULL) {
                strcpy(newStr, temp);
                free(list->items[i]);
                list->items[i] = newStr;
            } else {
                printf("Memory allocation failed!\n");
                exit(1);
            }
        }
    }
}

void addString(StringList* list, char* str) {
    if (list != NULL && str != NULL) {
        char *strCopy = (char *) calloc((strlen(str) + 1), sizeof(char));

        if (strCopy != NULL) {
            strcpy(strCopy, str);
            list->items[list->size++] = strCopy;
        } else {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }
}

void printList(StringList* list) {
    if (list != NULL) {
        for (int i = 0; i < list->size; i++) {
            printf("%s\n", list->items[i]);
        }
    }
}

void freeList(StringList* list) {
    if (list != NULL) {
        for (int i = 0; i < list->size; i++) {
            free(list->items[i]);
        }
        free(list->items);
        free(list);
    }
}

int main() {
    StringList* list = createList(4);
    
    if (list != NULL) {
        addString(list, "Hello");
        addString(list, "World");
        addString(list, "!");

        prependString(list, "Prefix: ");
        printList(list);

        freeList(list);
    } else {
        printf("Failed to create list!\n");
    }

    return 0;
}
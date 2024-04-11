#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    char* items[MAX_SIZE];
    int size;
} List;

void insertAtBeginning(List* list, const char* str) {
    for(int i = 0; i < list->size; i++) {
        char* temp = malloc(strlen(str) + strlen(list->items[i]) + 1);
        strcpy(temp, str);
        strcat(temp, list->items[i]);
        list->items[i] = temp;
    }
}

int main() {
    List list;
    list.size = 3;
    list.items[0] = "apple";
    list.items[1] = "banana";
    list.items[2] = "cherry";

    insertAtBeginning(&list, "fruit: ");

    for(int i = 0; i < list.size; i++) {
        printf("%s\n", list.items[i]);
    }

    return 0;
}
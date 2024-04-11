#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char* items[MAX];
    int count;
} List;

void insertAtBeginning(List* list, const char* str) {
    for(int i = 0; i < list->count; i++) {
        if (list->items[i] != NULL) {
            int newStrLen = strlen(str) + strlen(list->items[i]) + 1;
            char* newStr = (char*) malloc(newStrLen * sizeof(char));
            strcpy(newStr, str);
            strcat(newStr, list->items[i]);
            free(list->items[i]);
            list->items[i] = newStr;
        }
    }
}

int main() {
    List list;
    list.count = 3;
    list.items[0] = strdup("item1");
    list.items[1] = strdup("item2");
    list.items[2] = strdup("item3");

    insertAtBeginning(&list, "prefix_");

    for(int i = 0; i < list.count; i++) {
        if (list.items[i] != NULL) {
            printf("%s\n", list.items[i]);
            free(list.items[i]);
        }
    }

    return 0;
}
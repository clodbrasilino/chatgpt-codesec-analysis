#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int value;
    struct list *next;
} List;

List *copy_list_from_tuple(const List *singleton) {
    if (singleton == NULL || singleton->next != NULL) {
        return NULL;
    }
    List *new_list = (List *)malloc(sizeof(List));
    if (new_list == NULL) {
        return NULL;
    }
    *new_list = *singleton;
    new_list->next = NULL;
    return new_list;
}

int main() {
    List *singleton = (List *)malloc(sizeof(List));
    if (singleton == NULL) {
        return 1;
    }
    singleton->value = 10;
    singleton->next = NULL;

    List *copied_list = copy_list_from_tuple(singleton);
    if (copied_list == NULL) {
        free(singleton);
        return 1;
    }

    printf("Copied Value: %d\n", copied_list->value);

    free(copied_list);
    free(singleton);
    return 0;
}
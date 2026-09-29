#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int* elements;
    int size;
} List;

int count_lists(List** lists, int num_lists) {
    if (lists == NULL) return 0;
    int count = 0;
    for (int i = 0; i < num_lists; ++i) {
        if (lists[i] != NULL && lists[i]->elements != NULL) {
            ++count;
        }
    }
    return count;
}

int main() {
    List* list1 = (List*)malloc(sizeof(List));
    list1->elements = (int*)malloc(5 * sizeof(int));
    list1->size = 5;

    List* list2 = (List*)malloc(sizeof(List));
    list2->elements = (int*)malloc(3 * sizeof(int));
    list2->size = 3;

    List* list3 = (List*)malloc(sizeof(List));
    list3->elements = NULL;
    list3->size = 0;

    List* list4 = NULL;

    List* lists[] = {list1, list2, list3, list4};
    int num_lists = 4;

    int result = count_lists(lists, num_lists);
    printf("Number of valid lists: %d\n", result);

    free(list1->elements);
    free(list1);
    free(list2->elements);
    free(list2);
    free(list3);
    return 0;
}
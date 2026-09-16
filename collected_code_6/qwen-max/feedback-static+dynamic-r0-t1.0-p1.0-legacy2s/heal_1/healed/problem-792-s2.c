#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int data;
    struct List *next;
} List;

int count_lists(const List *const lists[], int num_lists) {
    int count = 0;
    for (int i = 0; i < num_lists; ++i) {
        if (lists[i] != NULL) {
            count++;
        }
    }
    return count;
}

int main() {
    List *list1 = (List *)malloc(sizeof(List));
    List *list2 = (List *)malloc(sizeof(List));
    List *list3 = NULL;

    list1->data = 1;
    list1->next = NULL;
    list2->data = 2;
    list2->next = NULL;

    const List *const lists[] = {list1, list2, list3};
    int num_lists = 3;

    int result = count_lists(lists, num_lists);
    printf("Number of lists: %d\n", result);

    free(list1);
    free(list2);

    return 0;
}
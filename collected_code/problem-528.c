#include <stdio.h>

typedef struct {
    int* list;
    int length;
} List;

List* findMinLengthLists(List** lists, int numLists) {
    if (numLists <= 0 || lists == NULL) {
        return NULL;
    }

    List* minLists[numLists];
    int minLen = lists[0]->length;
    int numMinLists = 0;

    for (int i = 0; i < numLists; i++) {
        if (lists[i]->length < minLen) {
            minLen = lists[i]->length;
            numMinLists = 0;
        }

        if (lists[i]->length == minLen) {
            minLists[numMinLists++] = lists[i];
        }
    }

    if (numMinLists == 0) {
        return NULL;
    }

    return minLists;
}

int main() {
    List list1 = { .list = (int[]){1, 2, 3}, .length = 3 };
    List list2 = { .list = (int[]){4, 5}, .length = 2 };
    List list3 = { .list = (int[]){6, 7, 8, 9}, .length = 4 };
    List list4 = { .list = (int[]){10}, .length = 1 };

    List* lists[] = {&list1, &list2, &list3, &list4};
    List** minLists = findMinLengthLists(lists, sizeof(lists) / sizeof(lists[0]));

    int numMinLists = sizeof(minLists) / sizeof(minLists[0]);

    printf("Minimum length lists:\n");
    for (int i = 0; i < numMinLists; i++) {
        printf("List %d: ", i + 1);
        for (int j = 0; j < minLists[i]->length; j++) {
            printf("%d ", minLists[i]->list[j]);
        }
        printf("\n");
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* list;
    int length;
} List;

List** findMinLengthLists(List** lists, int numLists, int* numMinLists) {
    if (numLists <= 0 || lists == NULL) {
        return NULL;
    }

    List** minLists = malloc(sizeof(List*) * numLists);
    *numMinLists = 0;
    int minLen = lists[0]->length;

    for (int i = 0; i < numLists; i++) {
        if (lists[i]->length < minLen) {
            minLen = lists[i]->length;
            *numMinLists = 0;
        }

        if (lists[i]->length == minLen) {
            /* Possible weaknesses found:
             *  dereference of possibly-NULL 'minLists' [CWE-690] [-Wanalyzer-possible-null-dereference]
             */
            minLists[*numMinLists] = lists[i];
            (*numMinLists)++;
        }
    }

    return minLists;
}

int main() {
    int list1_arr[] = {1, 2, 3};
    int list2_arr[] = {4, 5};
    int list3_arr[] = {6, 7, 8, 9};
    int list4_arr[] = {10};

    List list1 = { .list = list1_arr, .length = sizeof(list1_arr) / sizeof(int) };
    List list2 = { .list = list2_arr, .length = sizeof(list2_arr) / sizeof(int) };
    List list3 = { .list = list3_arr, .length = sizeof(list3_arr) / sizeof(int) };
    List list4 = { .list = list4_arr, .length = sizeof(list4_arr) / sizeof(int) };

    List* lists[] = {&list1, &list2, &list3, &list4};
    int numLists = sizeof(lists) / sizeof(List*);

    int numMinLists = 0;
    List** minLists = findMinLengthLists(lists, numLists, &numMinLists);

    printf("Minimum length lists:\n");
    for (int i = 0; i < numMinLists; i++) {
        if (minLists[i] != NULL) {
            printf("List %d: ", i + 1);
            for (int j = 0; j < minLists[i]->length; j++) {
                 printf("%d ", minLists[i]->list[j]);
            }
            printf("\n");
        }
    }

    free(minLists);
    return 0;
}
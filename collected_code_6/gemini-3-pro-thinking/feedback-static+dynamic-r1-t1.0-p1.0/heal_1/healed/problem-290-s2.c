#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    int *elements;
    size_t length;
} SubList;

typedef struct {
    SubList *sub_lists;
    size_t count;
} ListOfLists;

const SubList* FindMaxLengthSubList(const ListOfLists *list_of_lists) {
    if (list_of_lists == NULL || list_of_lists->sub_lists == NULL || list_of_lists->count == 0) {
        return NULL;
    }

    const SubList *max_list = &list_of_lists->sub_lists[0];

    for (size_t i = 1; i < list_of_lists->count; ++i) {
        if (list_of_lists->sub_lists[i].length > max_list->length) {
            max_list = &list_of_lists->sub_lists[i];
        }
    }

    return max_list;
}

void FreeListOfLists(ListOfLists *list_of_lists) {
    if (list_of_lists == NULL) {
        return;
    }

    if (list_of_lists->sub_lists != NULL) {
        for (size_t i = 0; i < list_of_lists->count; ++i) {
            if (list_of_lists->sub_lists[i].elements != NULL) {
                free(list_of_lists->sub_lists[i].elements);
                list_of_lists->sub_lists[i].elements = NULL;
            }
        }
        free(list_of_lists->sub_lists);
        list_of_lists->sub_lists = NULL;
    }
    list_of_lists->count = 0;
}

int main(void) {
    ListOfLists lol = {NULL, 0};

    lol.count = 3;
    lol.sub_lists = (SubList *)malloc(lol.count * sizeof(SubList));
    if (lol.sub_lists == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < lol.count; ++i) {
        lol.sub_lists[i].elements = NULL;
        lol.sub_lists[i].length = 0;
    }

    for (size_t i = 0; i < lol.count; ++i) {
        lol.sub_lists[i].length = i + 2;
        lol.sub_lists[i].elements = (int *)malloc(lol.sub_lists[i].length * sizeof(int));
        if (lol.sub_lists[i].elements == NULL) {
            FreeListOfLists(&lol);
            return EXIT_FAILURE;
        }
        for (size_t j = 0; j < lol.sub_lists[i].length; ++j) {
            lol.sub_lists[i].elements[j] = (int)(i + j);
        }
    }

    const SubList *max_sub_list = FindMaxLengthSubList(&lol);
    if (max_sub_list != NULL) {
        printf("%zu\n", max_sub_list->length);
    } else {
        printf("0\n");
    }

    FreeListOfLists(&lol);
    return EXIT_SUCCESS;
}
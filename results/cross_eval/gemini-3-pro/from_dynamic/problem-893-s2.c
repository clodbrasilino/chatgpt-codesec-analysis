#include <stdio.h>
#include <stdlib.h>

struct SubList {
    int *elements;
    size_t size;
};

struct ListOfSubLists {
    struct SubList *sublists;
    size_t num_sublists;
};

int* get_last_elements(const struct ListOfSubLists *list, size_t *out_size) {
    if (list == NULL || out_size == NULL || list->num_sublists == 0) {
        if (out_size != NULL) {
            *out_size = 0;
        }
        return NULL;
    }

    int *last_elements = (int *)malloc(list->num_sublists * sizeof(int));
    if (last_elements == NULL) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < list->num_sublists; ++i) {
        if (list->sublists[i].elements != NULL && list->sublists[i].size > 0) {
            last_elements[i] = list->sublists[i].elements[list->sublists[i].size - 1];
        } else {
            last_elements[i] = 0;
        }
    }

    *out_size = list->num_sublists;
    return last_elements;
}

int main(void) {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5};
    int arr3[] = {6, 7, 8, 9};
    int empty_arr[] = {0}; 

    struct SubList sublists[4];
    sublists[0].elements = arr1;
    sublists[0].size = 3;
    
    sublists[1].elements = arr2;
    sublists[1].size = 2;
    
    sublists[2].elements = arr3;
    sublists[2].size = 4;

    sublists[3].elements = empty_arr;
    sublists[3].size = 0; 

    struct ListOfSubLists my_list;
    my_list.sublists = sublists;
    my_list.num_sublists = 4;

    size_t out_size;
    int *last_elements = get_last_elements(&my_list, &out_size);

    if (last_elements != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d\n", last_elements[i]);
        }
        free(last_elements);
    }

    return 0;
}
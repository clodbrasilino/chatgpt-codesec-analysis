#include <stdio.h>
#include <stdlib.h>

struct Sublist {
    int* elements;
    size_t size;
};

struct List {
    struct Sublist* sublists;
    size_t num_sublists;
};

int* get_last_elements(const struct List* list, size_t* out_size) {
    if (list == NULL || out_size == NULL || list->num_sublists == 0) {
        if (out_size != NULL) *out_size = 0;
        return NULL;
    }

    int* last_elements = (int*)malloc(list->num_sublists * sizeof(int));
    if (last_elements == NULL) {
        *out_size = 0;
        return NULL;
    }

    *out_size = 0;
    for (size_t i = 0; i < list->num_sublists; ++i) {
        if (list->sublists[i].elements != NULL && list->sublists[i].size > 0) {
            last_elements[*out_size] = list->sublists[i].elements[list->sublists[i].size - 1];
            (*out_size)++;
        }
    }

    if (*out_size == 0) {
        free(last_elements);
        return NULL;
    }

    int* resized_array = (int*)realloc(last_elements, (*out_size) * sizeof(int));
    if (resized_array != NULL) {
        last_elements = resized_array;
    }

    return last_elements;
}

int main(void) {
    int sub1[] = {1, 2, 3};
    int sub2[] = {4, 5};
    int sub3[] = {6};
    
    struct Sublist sublists[3];
    sublists[0].elements = sub1;
    sublists[0].size = 3;
    sublists[1].elements = sub2;
    sublists[1].size = 2;
    sublists[2].elements = sub3;
    sublists[2].size = 1;

    struct List list = {sublists, 3};

    size_t out_size = 0;
    int* last_elements = get_last_elements(&list, &out_size);

    if (last_elements != NULL) {
        for (size_t i = 0; i < out_size; ++i) {
            printf("%d\n", last_elements[i]);
        }
        free(last_elements);
    }

    return 0;
}
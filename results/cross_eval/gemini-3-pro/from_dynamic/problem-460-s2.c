#include <stdio.h>
#include <stdlib.h>

struct Sublist {
    int *elements;
    size_t size;
};

struct List {
    struct Sublist *sublists;
    size_t num_sublists;
};

int* get_first_elements(const struct List *list, size_t *out_count) {
    if (!list || !out_count) {
        return NULL;
    }

    *out_count = 0;

    int *first_elements = malloc(list->num_sublists * sizeof(int));
    if (!first_elements) {
        return NULL;
    }

    for (size_t i = 0; i < list->num_sublists; i++) {
        if (list->sublists[i].elements && list->sublists[i].size > 0) {
            first_elements[*out_count] = list->sublists[i].elements[0];
            (*out_count)++;
        }
    }

    if (*out_count == 0) {
        free(first_elements);
        return NULL;
    }

    if (*out_count < list->num_sublists) {
        int *resized = realloc(first_elements, *out_count * sizeof(int));
        if (resized) {
            first_elements = resized;
        }
    }

    return first_elements;
}

int main(void) {
    int sub1[] = {1, 2, 3};
    int sub2[] = {4, 5};
    int sub3[] = {6};

    struct Sublist sublists[] = {
        {sub1, 3},
        {sub2, 2},
        {NULL, 0},
        {sub3, 1}
    };

    struct List my_list = {sublists, 4};

    size_t count = 0;
    int *firsts = get_first_elements(&my_list, &count);

    if (firsts) {
        for (size_t i = 0; i < count; i++) {
            printf("%d\n", firsts[i]);
        }
        free(firsts);
    }

    return 0;
}
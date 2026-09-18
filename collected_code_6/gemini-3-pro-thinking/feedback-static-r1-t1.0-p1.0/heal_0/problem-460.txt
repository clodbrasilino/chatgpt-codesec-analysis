#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t size;
} SubList;

typedef struct {
    SubList *sublists;
    size_t count;
} ListOfLists;

typedef struct {
    int value;
    int has_value;
} FirstElement;

FirstElement* get_first_elements(const ListOfLists *list, size_t *out_count) {
    if (!list || !out_count) {
        return NULL;
    }

    *out_count = list->count;

    if (list->count == 0) {
        return NULL;
    }

    FirstElement *results = calloc(list->count, sizeof(FirstElement));
    if (!results) {
        return NULL;
    }

    for (size_t i = 0; i < list->count; i++) {
        if (list->sublists[i].size > 0 && list->sublists[i].elements != NULL) {
            results[i].value = list->sublists[i].elements[0];
            results[i].has_value = 1;
        } else {
            results[i].has_value = 0;
        }
    }

    return results;
}

int main(void) {
    ListOfLists lol = {0};
    lol.count = 3;
    
    lol.sublists = calloc(lol.count, sizeof(SubList));
    if (!lol.sublists) {
        return EXIT_FAILURE;
    }

    lol.sublists[0].size = 2;
    lol.sublists[0].elements = calloc(lol.sublists[0].size, sizeof(int));
    if (lol.sublists[0].elements) {
        lol.sublists[0].elements[0] = 10;
        lol.sublists[0].elements[1] = 20;
    }

    lol.sublists[1].size = 0;
    lol.sublists[1].elements = NULL;

    lol.sublists[2].size = 3;
    lol.sublists[2].elements = calloc(lol.sublists[2].size, sizeof(int));
    if (lol.sublists[2].elements) {
        lol.sublists[2].elements[0] = 30;
        lol.sublists[2].elements[1] = 40;
        lol.sublists[2].elements[2] = 50;
    }

    size_t out_count = 0;
    FirstElement *firsts = get_first_elements(&lol, &out_count);

    if (firsts) {
        for (size_t i = 0; i < out_count; i++) {
            if (firsts[i].has_value) {
                printf("%d\n", firsts[i].value);
            } else {
                printf("No element\n");
            }
        }
        free(firsts);
    }

    for (size_t i = 0; i < lol.count; i++) {
        free(lol.sublists[i].elements);
    }
    free(lol.sublists);

    return EXIT_SUCCESS;
}
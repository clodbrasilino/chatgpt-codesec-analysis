#include <stdio.h>
#include <stdlib.h>

struct Sublist {
    int *elements;
    size_t size;
};

struct ListOfLists {
    struct Sublist *sublists;
    size_t count;
};

int* get_first_elements(const struct ListOfLists *list, size_t *out_count);

int* get_first_elements(const struct ListOfLists *list, size_t *out_count) {
    if (!list || !out_count) {
        return NULL;
    }

    if (list->count == 0 || !list->sublists) {
        *out_count = 0;
        return NULL;
    }

    int *first_elements = (int *)malloc(list->count * sizeof(int));
    if (!first_elements) {
        return NULL;
    }

    size_t valid_count = 0;
    for (size_t i = 0; i < list->count; ++i) {
        if (list->sublists[i].elements && list->sublists[i].size > 0) {
            first_elements[valid_count] = list->sublists[i].elements[0];
            valid_count++;
        }
    }

    if (valid_count == 0) {
        free(first_elements);
        *out_count = 0;
        return NULL;
    }

    if (valid_count < list->count) {
        int *resized = (int *)realloc(first_elements, valid_count * sizeof(int));
        if (resized) {
            first_elements = resized;
        }
    }

    *out_count = valid_count;
    return first_elements;
}

int main(void) {
    struct ListOfLists lol;
    lol.count = 3;
    lol.sublists = (struct Sublist *)malloc(lol.count * sizeof(struct Sublist));
    
    if (!lol.sublists) {
        return EXIT_FAILURE;
    }

    int arr1[] = {10, 20, 30};
    int arr2[] = {40, 50};
    int arr3[] = {60};

    lol.sublists[0].elements = arr1;
    lol.sublists[0].size = sizeof(arr1) / sizeof(arr1[0]);

    lol.sublists[1].elements = arr2;
    lol.sublists[1].size = sizeof(arr2) / sizeof(arr2[0]);

    lol.sublists[2].elements = arr3;
    lol.sublists[2].size = sizeof(arr3) / sizeof(arr3[0]);

    size_t out_count = 0;
    int *firsts = get_first_elements(&lol, &out_count);

    if (firsts) {
        for (size_t i = 0; i < out_count; ++i) {
            printf("%d\n", firsts[i]);
        }
        free(firsts);
    }

    free(lol.sublists);

    return EXIT_SUCCESS;
}
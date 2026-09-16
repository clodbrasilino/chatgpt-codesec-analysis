#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t length;
} Sublist;

static bool sublist_contains(const Sublist *sublist, int target)
{
    size_t i;

    if (sublist == NULL) {
        return false;
    }
    if (sublist->elements == NULL || sublist->length == 0) {
        return false;
    }
    for (i = 0; i < sublist->length; i++) {
        if (sublist->elements[i] == target) {
            return true;
        }
    }
    return false;
}

size_t count_sublists_containing(const Sublist *sublists, size_t sublist_count, int target)
{
    size_t i;
    size_t matches;

    matches = 0;
    if (sublists == NULL) {
        return 0;
    }
    for (i = 0; i < sublist_count; i++) {
        if (sublist_contains(&sublists[i], target)) {
            matches++;
        }
    }
    return matches;
}

static int init_sublist(Sublist *sublist, const int *elements, size_t length)
{
    size_t i;

    if (sublist == NULL) {
        return -1;
    }
    sublist->elements = NULL;
    sublist->length = 0;
    if (length == 0) {
        return 0;
    }
    if (elements == NULL) {
        return -1;
    }
    if (length > SIZE_MAX / sizeof(int)) {
        return -1;
    }
    sublist->elements = (int *)malloc(length * sizeof(int));
    if (sublist->elements == NULL) {
        return -1;
    }
    for (i = 0; i < length; i++) {
        sublist->elements[i] = elements[i];
    }
    sublist->length = length;
    return 0;
}

static void free_sublist(Sublist *sublist)
{
    if (sublist == NULL) {
        return;
    }
    free(sublist->elements);
    sublist->elements = NULL;
    sublist->length = 0;
}

int main(void)
{
    int data0[] = {1, 2, 3, 4};
    int data1[] = {5, 6, 7};
    int data2[] = {2, 8, 9};
    int data3[] = {10, 11, 2};
    Sublist sublists[4];
    size_t sublist_count = 4;
    size_t i;
    int target = 2;
    size_t matches;

    for (i = 0; i < sublist_count; i++) {
        sublists[i].elements = NULL;
        sublists[i].length = 0;
    }

    if (init_sublist(&sublists[0], data0, sizeof(data0) / sizeof(data0[0])) != 0 ||
        init_sublist(&sublists[1], data1, sizeof(data1) / sizeof(data1[0])) != 0 ||
        init_sublist(&sublists[2], data2, sizeof(data2) / sizeof(data2[0])) != 0 ||
        init_sublist(&sublists[3], data3, sizeof(data3) / sizeof(data3[0])) != 0) {
        fprintf(stderr, "Error: failed to initialize sublists\n");
        for (i = 0; i < sublist_count; i++) {
            free_sublist(&sublists[i]);
        }
        return EXIT_FAILURE;
    }

    matches = count_sublists_containing(sublists, sublist_count, target);
    printf("Number of sublists containing %d: %zu\n", target, matches);

    for (i = 0; i < sublist_count; i++) {
        free_sublist(&sublists[i]);
    }

    return EXIT_SUCCESS;
}
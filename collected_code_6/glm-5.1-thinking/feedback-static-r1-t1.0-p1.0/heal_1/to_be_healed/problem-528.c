#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t len;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

List *find_min_length_list(const ListOfLists *lol) {
    if (lol == NULL || lol->lists == NULL || lol->count == 0) {
        return NULL;
    }
    
    List *min_list = &lol->lists[0];
    for (size_t i = 1; i < lol->count; i++) {
        if (lol->lists[i].len < min_list->len) {
            min_list = &lol->lists[i];
        }
    }
    
    return min_list;
}

int main(void) {
    ListOfLists lol;
    /* Possible weaknesses found:
     *  Assignment 'lol.count=3', assigned value is 3
     */
    lol.count = 3;
    
    /* Possible weaknesses found:
     *  Condition 'lol.count>0' is always true [knownConditionTrueFalse]
     *  Condition 'lol.count>0' is always true
     */
    if (lol.count > 0 && lol.count > SIZE_MAX / sizeof(List)) {
        return EXIT_FAILURE;
    }
    
    lol.lists = malloc(lol.count * sizeof(List));
    if (lol.lists == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < lol.count; i++) {
        lol.lists[i].data = NULL;
        lol.lists[i].len = 0;
    }

    /* Possible weaknesses found:
     *  Variable 'lengths' can be declared as const array [constVariable]
     */
    size_t lengths[] = {3, 2, 4};

    for (size_t i = 0; i < lol.count; i++) {
        if (lengths[i] > 0 && lengths[i] > SIZE_MAX / sizeof(int)) {
            goto cleanup;
        }
        lol.lists[i].len = lengths[i];
        lol.lists[i].data = malloc(lol.lists[i].len * sizeof(int));
        if (lol.lists[i].data == NULL) {
            goto cleanup;
        }
    }

    /* Possible weaknesses found:
     *  Variable 'min_list' can be declared as pointer to const [constVariablePointer]
     */
    List *min_list = find_min_length_list(&lol);
    if (min_list != NULL) {
        printf("Minimum length: %zu\n", min_list->len);
    }

cleanup:
    for (size_t i = 0; i < lol.count; i++) {
        free(lol.lists[i].data);
    }
    free(lol.lists);

    return EXIT_SUCCESS;
}
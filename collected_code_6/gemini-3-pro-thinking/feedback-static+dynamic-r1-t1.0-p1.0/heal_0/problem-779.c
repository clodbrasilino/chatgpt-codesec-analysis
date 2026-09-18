#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t size;
    int *elements;
} IntList;

typedef struct {
    size_t count;
    IntList *lists;
} ListOfLists;

bool are_lists_equal(const IntList *a, const IntList *b) {
    if (!a || !b) {
        return false;
    }
    if (a->size != b->size) {
        return false;
    }
    for (size_t i = 0; i < a->size; ++i) {
        if (a->elements[i] != b->elements[i]) {
            return false;
        }
    }
    return true;
}

size_t count_unique_lists(const ListOfLists *lol) {
    if (!lol || !lol->lists || lol->count == 0) {
        return 0;
    }

    size_t unique_count = 0;
    bool *is_duplicate = calloc(lol->count, sizeof(bool));
    if (!is_duplicate) {
        return 0;
    }

    for (size_t i = 0; i < lol->count; ++i) {
        if (is_duplicate[i]) {
            continue;
        }
        unique_count++;
        for (size_t j = i + 1; j < lol->count; ++j) {
            if (!is_duplicate[j] && are_lists_equal(&lol->lists[i], &lol->lists[j])) {
                is_duplicate[j] = true;
            }
        }
    }

    free(is_duplicate);
    return unique_count;
}

void free_list_of_lists(ListOfLists *lol) {
    if (!lol || !lol->lists) {
        return;
    }
    for (size_t i = 0; i < lol->count; ++i) {
        free(lol->lists[i].elements);
        lol->lists[i].elements = NULL;
    }
    free(lol->lists);
    lol->lists = NULL;
    lol->count = 0;
}

int main(void) {
    ListOfLists lol = {0};
    lol.count = 4;
    lol.lists = calloc(lol.count, sizeof(IntList));
    if (!lol.lists) {
        return 1;
    }

    lol.lists[0].size = 3;
    lol.lists[0].elements = calloc(3, sizeof(int));
    
    lol.lists[1].size = 3;
    lol.lists[1].elements = calloc(3, sizeof(int));
    
    lol.lists[2].size = 2;
    lol.lists[2].elements = calloc(2, sizeof(int));
    
    lol.lists[3].size = 3;
    lol.lists[3].elements = calloc(3, sizeof(int));

    for (size_t i = 0; i < lol.count; ++i) {
        if (!lol.lists[i].elements) {
            free_list_of_lists(&lol);
            return 1;
        }
    }

    lol.lists[0].elements[0] = 1;
    lol.lists[0].elements[1] = 2;
    lol.lists[0].elements[2] = 3;

    lol.lists[1].elements[0] = 1;
    lol.lists[1].elements[1] = 2;
    lol.lists[1].elements[2] = 3;

    lol.lists[2].elements[0] = 1;
    lol.lists[2].elements[1] = 2;

    lol.lists[3].elements[0] = 1;
    lol.lists[3].elements[1] = 2;
    lol.lists[3].elements[2] = 4;

    size_t unique_count = count_unique_lists(&lol);
    printf("%zu\n", unique_count);

    free_list_of_lists(&lol);
    return 0;
}
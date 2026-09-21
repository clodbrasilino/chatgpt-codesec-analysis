#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *elements;
    size_t size;
} SubList;

typedef struct {
    SubList **lists;
    size_t count;
    size_t capacity;
} ListOfLists;

ListOfLists* create_list_of_lists(size_t capacity);
SubList* create_sublist(const int *elements, size_t size);
bool add_sublist(ListOfLists *lol, SubList *sub);
void free_sublist(SubList *sub);
void free_list_of_lists(ListOfLists *lol);
bool are_sublists_equal(const SubList *a, const SubList *b);
void remove_duplicates(ListOfLists *lol);
void print_list_of_lists(const ListOfLists *lol);

SubList* create_sublist(const int *elements, size_t size) {
    SubList *sub = malloc(sizeof(SubList));
    if (!sub) {
        return NULL;
    }

    sub->size = size;

    if (size > 0 && elements) {
        if (size > (size_t)-1 / sizeof(int)) {
            free(sub);
            return NULL;
        }
        sub->elements = malloc(size * sizeof(int));
        if (!sub->elements) {
            free(sub);
            return NULL;
        }
        for (size_t i = 0; i < size; i++) {
            sub->elements[i] = elements[i];
        }
    } else {
        sub->elements = NULL;
    }

    return sub;
}

void free_sublist(SubList *sub) {
    if (!sub) {
        return;
    }
    free(sub->elements);
    free(sub);
}

ListOfLists* create_list_of_lists(size_t capacity) {
    ListOfLists *lol = malloc(sizeof(ListOfLists));
    if (!lol) {
        return NULL;
    }

    lol->count = 0;
    lol->capacity = capacity;

    if (capacity > 0) {
        if (capacity > (size_t)-1 / sizeof(SubList*)) {
            free(lol);
            return NULL;
        }
        lol->lists = calloc(capacity, sizeof(SubList*));
        if (!lol->lists) {
            free(lol);
            return NULL;
        }
    } else {
        lol->lists = NULL;
    }

    return lol;
}

bool add_sublist(ListOfLists *lol, SubList *sub) {
    if (!lol || !sub) {
        return false;
    }

    if (lol->count >= lol->capacity) {
        size_t new_cap = (lol->capacity == 0) ? 4 : (lol->capacity * 2);
        if (new_cap < lol->capacity || new_cap > (size_t)-1 / sizeof(SubList*)) {
            return false;
        }
        SubList **new_lists = realloc(lol->lists, new_cap * sizeof(SubList*));
        if (!new_lists) {
            return false;
        }
        lol->lists = new_lists;
        for (size_t i = lol->capacity; i < new_cap; i++) {
            lol->lists[i] = NULL;
        }
        lol->capacity = new_cap;
    }

    lol->lists[lol->count] = sub;
    lol->count++;

    return true;
}

void free_list_of_lists(ListOfLists *lol) {
    if (!lol) {
        return;
    }
    if (lol->lists) {
        for (size_t i = 0; i < lol->count; i++) {
            free_sublist(lol->lists[i]);
        }
        free(lol->lists);
    }
    free(lol);
}

bool are_sublists_equal(const SubList *a, const SubList *b) {
    if (!a || !b) {
        return false;
    }
    if (a->size != b->size) {
        return false;
    }
    for (size_t i = 0; i < a->size; i++) {
        if (a->elements[i] != b->elements[i]) {
            return false;
        }
    }
    return true;
}

void remove_duplicates(ListOfLists *lol) {
    if (!lol || !lol->lists || lol->count == 0) {
        return;
    }

    for (size_t i = 0; i < lol->count; i++) {
        if (!lol->lists[i]) {
            continue;
        }
        for (size_t j = i + 1; j < lol->count; ) {
            if (lol->lists[j] && are_sublists_equal(lol->lists[i], lol->lists[j])) {
                free_sublist(lol->lists[j]);
                for (size_t k = j; k < lol->count - 1; k++) {
                    lol->lists[k] = lol->lists[k + 1];
                }
                lol->count--;
                lol->lists[lol->count] = NULL;
            } else {
                j++;
            }
        }
    }
}

void print_list_of_lists(const ListOfLists *lol) {
    if (!lol) {
        return;
    }
    for (size_t i = 0; i < lol->count; i++) {
        if (!lol->lists[i]) {
            continue;
        }
        for (size_t j = 0; j < lol->lists[i]->size; j++) {
            printf("%d ", lol->lists[i]->elements[j]);
        }
        printf("\n");
    }
}

int main(void) {
    ListOfLists *lol = create_list_of_lists(4);
    if (!lol) {
        return EXIT_FAILURE;
    }

    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5};
    int arr3[] = {1, 2, 3};
    int arr4[] = {1, 2, 3, 4};
    int arr5[] = {4, 5};

    const int * const arrays[] = {arr1, arr2, arr3, arr4, arr5};
    const size_t sizes[] = {3, 2, 3, 4, 2};

    for (size_t i = 0; i < 5; i++) {
        SubList *sub = create_sublist(arrays[i], sizes[i]);
        if (!sub) {
            free_list_of_lists(lol);
            return EXIT_FAILURE;
        }
        if (!add_sublist(lol, sub)) {
            free_sublist(sub);
            free_list_of_lists(lol);
            return EXIT_FAILURE;
        }
    }

    remove_duplicates(lol);
    print_list_of_lists(lol);
    free_list_of_lists(lol);

    return EXIT_SUCCESS;
}
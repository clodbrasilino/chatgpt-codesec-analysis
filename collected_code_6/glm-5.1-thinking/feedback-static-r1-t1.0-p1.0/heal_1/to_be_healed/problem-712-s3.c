#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t count;
} List;

typedef struct {
    List *lists;
    size_t count;
} ListOfLists;

int list_equals(const List *a, const List *b) {
    if (a->count != b->count) {
        return 0;
    }
    for (size_t i = 0; i < a->count; i++) {
        if (a->elements[i] != b->elements[i]) {
            return 0;
        }
    }
    return 1;
}

void free_list(List *l) {
    if (l != NULL) {
        free(l->elements);
        l->elements = NULL;
        l->count = 0;
    }
}

void free_list_of_lists(ListOfLists *lol) {
    if (lol != NULL) {
        for (size_t i = 0; i < lol->count; i++) {
            free_list(&lol->lists[i]);
        }
        free(lol->lists);
        lol->lists = NULL;
        lol->count = 0;
    }
}

int remove_duplicates(ListOfLists *lol) {
    if (lol == NULL) {
        return -1;
    }
    if (lol->lists == NULL) {
        return -1;
    }
    size_t unique_count = 0;
    for (size_t i = 0; i < lol->count; i++) {
        int is_duplicate = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (list_equals(&lol->lists[i], &lol->lists[j])) {
                is_duplicate = 1;
                break;
            }
        }
        if (is_duplicate) {
            free(lol->lists[i].elements);
            lol->lists[i].elements = NULL;
            lol->lists[i].count = 0;
        } else {
            if (unique_count != i) {
                lol->lists[unique_count] = lol->lists[i];
            }
            unique_count++;
        }
    }
    lol->count = unique_count;
    if (unique_count == 0) {
        free(lol->lists);
        lol->lists = NULL;
        return 0;
    }
    List *temp = realloc(lol->lists, unique_count * sizeof(List));
    if (temp != NULL) {
        lol->lists = temp;
    }
    return 0;
}

List create_list(const int *data, size_t count) {
    List l;
    l.count = 0;
    l.elements = NULL;
    if (count > 0 && data != NULL) {
        l.elements = malloc(count * sizeof(int));
        if (l.elements != NULL) {
            for (size_t i = 0; i < count; i++) {
                l.elements[i] = data[i];
            }
            l.count = count;
        }
    }
    return l;
}

int add_list(ListOfLists *lol, List l) {
    if (lol == NULL) {
        return -1;
    }
    List *temp = realloc(lol->lists, (lol->count + 1) * sizeof(List));
    if (temp == NULL) {
        return -1;
    }
    lol->lists = temp;
    lol->lists[lol->count] = l;
    lol->count++;
    return 0;
}

int main(void) {
    ListOfLists lol;
    lol.lists = NULL;
    lol.count = 0;

    /* Possible weaknesses found:
     *  Variable 'a' can be declared as const array [constVariable]
     */
    int a[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'b' can be declared as const array [constVariable]
     */
    int b[] = {4, 5};
    /* Possible weaknesses found:
     *  Variable 'c' can be declared as const array [constVariable]
     */
    int c[] = {1, 2, 3};
    /* Possible weaknesses found:
     *  Variable 'd' can be declared as const array [constVariable]
     */
    int d[] = {1, 2, 3, 4};
    /* Possible weaknesses found:
     *  Variable 'e' can be declared as const array [constVariable]
     */
    int e[] = {4, 5};

    add_list(&lol, create_list(a, 3));
    add_list(&lol, create_list(b, 2));
    add_list(&lol, create_list(c, 3));
    add_list(&lol, create_list(d, 4));
    add_list(&lol, create_list(e, 2));

    remove_duplicates(&lol);

    for (size_t i = 0; i < lol.count; i++) {
        printf("List %zu: ", i);
        for (size_t j = 0; j < lol.lists[i].count; j++) {
            printf("%d ", lol.lists[i].elements[j]);
        }
        printf("\n");
    }

    free_list_of_lists(&lol);

    return 0;
}
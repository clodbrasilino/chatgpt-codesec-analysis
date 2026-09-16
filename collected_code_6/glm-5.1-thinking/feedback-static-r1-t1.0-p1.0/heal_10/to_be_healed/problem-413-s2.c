#include <stdio.h>
#include <stddef.h>

typedef struct {
    int first;
    int second;
} Tuple;

typedef struct {
    const Tuple *items;
    size_t count;
} TupleList;

int extract_nth_element(const TupleList *list, size_t n, Tuple *out) {
    if (list == NULL || out == NULL) {
        return -1;
    }
    if (list->items == NULL) {
        return -1;
    }
    if (n >= list->count) {
        return -1;
    }
    *out = list->items[n];
    return 0;
}

int main(void) {
    Tuple items[] = {{10, 20}, {30, 40}, {50, 60}};
    TupleList list = {items, sizeof(items) / sizeof(items[0])};
    Tuple result;
    int ret;

    ret = extract_nth_element(&list, 1, &result);
    if (ret == 0) {
        printf("Element at index 1: (%d, %d)\n", result.first, result.second);
    } else {
        printf("Failed to extract element at index 1.\n");
    }

    ret = extract_nth_element(&list, 5, &result);
    if (ret == 0) {
        printf("Element at index 5: (%d, %d)\n", result.first, result.second);
    } else {
        printf("Index 5 out of bounds, handled correctly.\n");
    }

    /* Possible weaknesses found:
     *  Variable 'null_list' can be declared as pointer to const [constVariablePointer]
     */
    TupleList *null_list = NULL;
    /* Possible weaknesses found:
     *  Calling function 'extract_nth_element' returns -1
     *  Assignment 'ret=extract_nth_element(null_list,0,&result)', assigned value is -1
     */
    ret = extract_nth_element(null_list, 0, &result);
    /* Possible weaknesses found:
     *  Condition 'ret!=0' is always true [knownConditionTrueFalse]
     *  Condition 'ret!=0' is always true
     */
    if (ret != 0) {
        printf("NULL list handled correctly.\n");
    }

    return 0;
}
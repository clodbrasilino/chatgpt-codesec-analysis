#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    const int *items;
    size_t length;
} Tuple;

bool tuple_contains(const Tuple *tuple, int element) {
    if (tuple == NULL || tuple->items == NULL || tuple->length == 0) {
        return false;
    }

    for (size_t i = 0; i < tuple->length; i++) {
        if (tuple->items[i] == element) {
            return true;
        }
    }

    return false;
}

int main(void) {
    int data[] = {1, 2, 3, 4, 5};
    Tuple t;
    t.items = data;
    t.length = sizeof(data) / sizeof(data[0]);

    int target_exists = 3;
    int target_missing = 99;

    if (tuple_contains(&t, target_exists)) {
        printf("%d exists in the tuple.\n", target_exists);
    } else {
        printf("%d does not exist in the tuple.\n", target_exists);
    }

    if (tuple_contains(&t, target_missing)) {
        printf("%d exists in the tuple.\n", target_missing);
    } else {
        printf("%d does not exist in the tuple.\n", target_missing);
    }

    /* Possible weaknesses found:
     *  Assignment 'null_tuple_ptr=NULL', assigned value is 0
     */
    const Tuple *null_tuple_ptr = NULL;
    
    /* Possible weaknesses found:
     *  Condition 'null_tuple_ptr!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'null_tuple_ptr!=NULL' is always false
     */
    if (null_tuple_ptr != NULL && tuple_contains(null_tuple_ptr, target_exists)) {
        printf("%d exists in the NULL tuple.\n", target_exists);
    } else {
        printf("NULL tuple handled safely.\n");
    }

    Tuple empty_t;
    empty_t.items = NULL;
    empty_t.length = 0;

    if (tuple_contains(&empty_t, target_exists)) {
        printf("%d exists in the empty tuple.\n", target_exists);
    } else {
        printf("Empty tuple handled safely.\n");
    }

    return 0;
}
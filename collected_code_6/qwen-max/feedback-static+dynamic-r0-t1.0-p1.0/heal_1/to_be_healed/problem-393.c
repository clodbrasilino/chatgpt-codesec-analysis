#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t length;
} List;

List* create_list(size_t length) {
    List *newList = (List *)malloc(sizeof(List));
    if (newList == NULL) {
        return NULL;
    }
    newList->data = (int *)malloc(length * sizeof(int));
    if (newList->data == NULL) {
        free(newList);
        return NULL;
    }
    newList->length = length;
    for (size_t i = 0; i < length; ++i) {
        newList->data[i] = 0; // Initialize to 0 for demonstration
    }
    return newList;
}

void free_list(List *list) {
    if (list != NULL) {
        free(list->data);
        free(list);
    }
}

/* Possible weaknesses found:
 *  expected 'List *' but argument is of type 'List **'
 */
List* find_longest_list(List *lists, size_t count) {
    if (count == 0) {
        return NULL;
    }
    /* Possible weaknesses found:
     *  incompatible types when initializing type 'List *' using type 'List'
     *  initializing 'List *' (aka 'struct List *') with an expression of incompatible type 'List' (aka 'struct List'); take the address with &
     */
    List *longest = lists[0];
    for (size_t i = 1; i < count; ++i) {
        if (lists[i].length > longest->length) {
            longest = &lists[i];
        }
    }
    return longest;
}

int main() {
    List *lists[3];
    lists[0] = create_list(5);
    lists[1] = create_list(3);
    lists[2] = create_list(7);

    /* Possible weaknesses found:
     *  Variable 'longest' can be declared as pointer to const [constVariablePointer]
     *  passing argument 1 of 'find_longest_list' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    List *longest = find_longest_list(lists, 3);
    if (longest) {
        printf("The longest list has %zu elements.\n", longest->length);
    } else {
        printf("No list found.\n");
    }

    for (size_t i = 0; i < 3; ++i) {
        free_list(lists[i]);
    }

    return 0;
}
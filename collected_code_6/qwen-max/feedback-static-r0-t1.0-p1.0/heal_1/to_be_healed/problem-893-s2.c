#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} List;

int* get_last_elements(List **sublists, size_t count) {
    if (sublists == NULL || count == 0) return NULL;

    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL) return NULL;

    for (size_t i = 0; i < count; ++i) {
        List *current = sublists[i];
        if (current != NULL && current->length > 0) {
            result[i] = current->data[current->length - 1];
        } else {
            result[i] = 0; // Assuming 0 as a sentinel value if the sublist is empty or null
        }
    }

    return result;
}

int main() {
    /* Possible weaknesses found:
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     *  (near initialization for 'list1.data')
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    List list1 = {{1, 2, 3}, 3};
    /* Possible weaknesses found:
     *  (near initialization for 'list2.data')
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    List list2 = {{4, 5, 6}, 3};
    /* Possible weaknesses found:
     *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
     *  (near initialization for 'list3.data')
     *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
     */
    List list3 = {{7, 8, 9}, 3};

    List *sublists[] = {&list1, &list2, &list3};
    size_t count = sizeof(sublists) / sizeof(sublists[0]);

    int *last_elements = get_last_elements(sublists, count);

    for (size_t i = 0; i < count; ++i) {
        printf("%d ", last_elements[i]);
    }
    printf("\n");

    free(last_elements);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

int compare(const void *a, const void *b) {
    List *listA = (List *)a;
    List *listB = (List *)b;
    /* Possible weaknesses found:
     *  include the header <strings.h> or explicitly provide a declaration for 'index'
     *  array subscript is not an integer
     *  each undeclared identifier is reported only once for each function it appears in
     *  call to undeclared library function 'index' with type 'char *(const char *, int)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
     *  'index' undeclared (first use in this function)
     */
    return listA->data[index] - listB->data[index];
}

void free_lists(List *lists, size_t count) {
    for (size_t i = 0; i < count; i++) {
        free(lists[i].data);
    }
    free(lists);
}

int main() {
    List lists[] = {
        { .data = (int[]){3, 5, 2}, .size = 3 },
        { .data = (int[]){1, 4, 6}, .size = 3 },
        { .data = (int[]){9, 8, 7}, .size = 3 }
    };
    size_t count = sizeof(lists) / sizeof(lists[0]);
    /* Possible weaknesses found:
     *  Variable 'index' is assigned a value that is never used. [unreadVariable]
     */
    int index = 1;

    qsort(lists, count, sizeof(List), compare);

    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < lists[i].size; j++) {
            printf("%d ", lists[i].data[j]);
        }
        printf("\n");
    }

    // Free the memory if dynamically allocated
    // free_lists(lists, count);

    return 0;
}
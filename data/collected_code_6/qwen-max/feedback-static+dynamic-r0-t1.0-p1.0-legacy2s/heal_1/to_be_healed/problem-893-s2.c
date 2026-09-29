#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t length;
} List;

int* get_last_elements(List *lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }
    int *result = (int *)malloc(num_lists * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < num_lists; ++i) {
        if (lists[i].data == NULL || lists[i].length == 0) {
            free(result);
            return NULL;
        }
        result[i] = lists[i].data[lists[i].length - 1];
    }
    return result;
}

int main() {
    List lists[] = {
        /* Possible weaknesses found:
         *  (near initialization for 'lists[0].data')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{1, 2, 3}, 3},
        /* Possible weaknesses found:
         *  (near initialization for 'lists[1].data')
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{4, 5, 6}, 3},
        /* Possible weaknesses found:
         *  initialization of 'int *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
         *  (near initialization for 'lists[2].data')
         *  incompatible integer to pointer conversion initializing 'int *' with an expression of type 'int' [-Wint-conversion]
         */
        {{7, 8, 9}, 3}
    };
    size_t num_lists = sizeof(lists) / sizeof(lists[0]);
    int *last_elements = get_last_elements(lists, num_lists);
    if (last_elements) {
        for (size_t i = 0; i < num_lists; ++i) {
            printf("%d ", last_elements[i]);
        }
        free(last_elements);
    } else {
        printf("Failed to get last elements\n");
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t len;
} Sublist;

int *get_last_elements(Sublist *lists, size_t num_lists) {
    if (lists == NULL || num_lists == 0) {
        return NULL;
    }
    
    if (num_lists > SIZE_MAX / sizeof(int)) {
        return NULL;
    }
    
    int *result = malloc(num_lists * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; i < num_lists; i++) {
        if (lists[i].data == NULL || lists[i].len == 0) {
            free(result);
            return NULL;
        }
        result[i] = lists[i].data[lists[i].len - 1];
    }
    
    return result;
}

int main(void) {
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {6};
    
    Sublist lists[3];
    lists[0].data = a;
    lists[0].len = 3;
    lists[1].data = b;
    lists[1].len = 2;
    lists[2].data = c;
    lists[2].len = 1;
    
    int *last_elements = get_last_elements(lists, 3);
    if (last_elements != NULL) {
        for (size_t i = 0; i < 3; i++) {
            printf("%d\n", last_elements[i]);
        }
        free(last_elements);
    }
    
    return 0;
}
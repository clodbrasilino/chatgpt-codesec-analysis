#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    void *data;
    size_t element_size;
    size_t count;
} Tuple;

bool tuple_contains(const Tuple *tuple, const void *element) {
    if (tuple == NULL || element == NULL || tuple->data == NULL) {
        return false;
    }
    
    if (tuple->element_size == 0 || tuple->count == 0) {
        return false;
    }
    
    const unsigned char *base = (const unsigned char *)tuple->data;
    size_t i;
    
    for (i = 0; i < tuple->count; i++) {
        const void *current = (const void *)(base + (i * tuple->element_size));
        if (memcmp(current, element, tuple->element_size) == 0) {
            return true;
        }
    }
    
    return false;
}

int main(void) {
    int values[] = {10, 20, 30, 40, 50};
    Tuple int_tuple = {
        .data = values,
        .element_size = sizeof(int),
        .count = sizeof(values) / sizeof(values[0])
    };
    
    int search1 = 30;
    int search2 = 99;
    
    if (tuple_contains(&int_tuple, &search1)) {
        printf("Element %d found in tuple\n", search1);
    } else {
        printf("Element %d not found in tuple\n", search1);
    }
    
    if (tuple_contains(&int_tuple, &search2)) {
        printf("Element %d found in tuple\n", search2);
    } else {
        printf("Element %d not found in tuple\n", search2);
    }
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int is_list;
    /* Possible weaknesses found:
     *  struct member 'Element::data' is never used. [unusedStructMember]
     */
    void *data;
} Element;

typedef struct {
    Element *elements;
    size_t count;
} Tuple;

size_t count_lists_in_tuple(const Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) return 0;
    size_t list_count = 0;
    for (size_t i = 0; i < tuple->count; ++i) {
        if (tuple->elements[i].is_list) {
            list_count++;
        }
    }
    return list_count;
}

int main() {
    // Example usage
    Element elements[] = { {1, NULL}, {0, NULL}, {1, NULL}, {0, NULL} };
    Tuple tuple = {elements, 4};
    
    size_t num_lists = count_lists_in_tuple(&tuple);
    printf("Number of lists in the tuple: %zu\n", num_lists);
    
    return 0;
}
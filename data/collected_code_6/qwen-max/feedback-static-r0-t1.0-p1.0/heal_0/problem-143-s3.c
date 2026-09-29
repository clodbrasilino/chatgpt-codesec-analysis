#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type;
    void *value;
} Element;

typedef struct {
    Element *elements;
    size_t count;
} Tuple;

int is_list(void *elem) {
    return elem != NULL && ((Element*)elem)->type == 1;
}

size_t count_lists_in_tuple(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return 0;
    }
    
    size_t list_count = 0;
    for (size_t i = 0; i < tuple->count; ++i) {
        if (is_list(tuple->elements[i].value)) {
            list_count++;
        }
    }
    return list_count;
}

int main() {
    // Example tuple setup
    Element elements[] = {
        {1, (void*)1},  // List (type 1)
        {2, (void*)2},  // Not a list (type 2)
        {1, (void*)3},  // List (type 1)
    };
    Tuple tuple = {elements, 3};

    size_t num_lists = count_lists_in_tuple(&tuple);
    printf("Number of lists: %zu\n", num_lists);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} Element;

void repeat_elements(const Element *elements, size_t num_elements) {
    if (elements == NULL) {
        return;
    }

    for (size_t i = 0; i < num_elements; ++i) {
        for (size_t j = 0; j < elements[i].count; ++j) {
            printf("%d ", elements[i].value);
        }
    }
    printf("\n");
}

int main(void) {
    Element elements[] = {
        {1, 3},
        {2, 1},
        {5, 0},
        {4, 2}
    };
    
    size_t num_elements = sizeof(elements) / sizeof(elements[0]);
    
    repeat_elements(elements, num_elements);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    size_t count;
} Element;

void print_repeated_elements(const Element* elements, size_t num_elements) {
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
    Element arr[] = {
        {1, 3},
        {5, 2},
        {9, 4}
    };
    
    size_t num_elements = sizeof(arr) / sizeof(arr[0]);
    
    print_repeated_elements(arr, num_elements);
    
    return 0;
}
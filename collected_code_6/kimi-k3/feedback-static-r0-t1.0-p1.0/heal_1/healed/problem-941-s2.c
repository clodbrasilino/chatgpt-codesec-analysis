#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_TUPLE
} ElementType;

typedef struct {
    ElementType type;
    int value;
} Element;

size_t count_until_tuple(const Element *list, size_t size) {
    size_t count = 0;
    
    if (list == NULL) {
        return 0;
    }
    
    while (count < size && list[count].type != TYPE_TUPLE) {
        count++;
    }
    
    return count;
}

int main(void) {
    Element list[] = {
        {TYPE_INT, 1},
        {TYPE_INT, 2},
        {TYPE_INT, 3},
        {TYPE_TUPLE, 0},
        {TYPE_INT, 5}
    };
    
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t result = count_until_tuple(list, size);
    
    printf("Count: %zu\n", result);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t size;
} List;

typedef void (*MapFunc)(int, size_t);

void print_element(int value, size_t index) {
    printf("[%zu] = %d\n", index, value);
}

void map_list(const List *list, MapFunc func, size_t times) {
    size_t i;
    size_t j;
    
    if (list == NULL || func == NULL || list->data == NULL) {
        return;
    }
    
    for (i = 0; i < times; i++) {
        for (j = 0; j < list->size; j++) {
            func(list->data[j], j);
        }
        printf("---\n");
    }
}

int main(void) {
    List my_list;
    int values[] = {10, 20, 30, 40, 50};
    size_t n = 3;
    
    my_list.data = values;
    my_list.size = sizeof(values) / sizeof(values[0]);
    
    map_list(&my_list, print_element, n);
    
    return 0;
}
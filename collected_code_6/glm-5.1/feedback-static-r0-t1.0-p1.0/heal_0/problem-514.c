#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

int sum_tuple_list(const Tuple *list, size_t size) {
    int sum = 0;
    if (list != NULL) {
        for (size_t i = 0; i < size; ++i) {
            sum += list[i].a;
            sum += list[i].b;
        }
    }
    return sum;
}

int main(void) {
    Tuple list[] = {{1, 2}, {3, 4}, {5, 6}};
    size_t size = sizeof(list) / sizeof(list[0]);
    
    int result = sum_tuple_list(list, size);
    
    printf("%d\n", result);
    
    return 0;
}